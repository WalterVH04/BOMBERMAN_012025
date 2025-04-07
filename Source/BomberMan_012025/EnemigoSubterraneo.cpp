// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoSubterraneo.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "BloqueConcreto.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

AEnemigoSubterraneo::AEnemigoSubterraneo()
{
	PrimaryActorTick.bCanEverTick = true;

	if (MeshEnemigo)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"));

		if (MaterialBase.Succeeded())
		{
			MeshEnemigo->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
		}
	}

	// Inicializar la dirección de movimiento
	MovimientoDireccion = FVector(1.0f, 0.0f, 0.0f); // Por ejemplo, moverse en el eje X positivo

	// Inicializar la velocidad de rotación
	VelocidadRotacion = 45.0f; // Rotar 45 grados por segundo

	// Inicializar la bandera de detención
	bEstaDetenido = false;
}

void AEnemigoSubterraneo::BeginPlay()
{
	Super::BeginPlay();

	// Iniciar el temporizador para la teletransportación
	GetWorld()->GetTimerManager().SetTimer(TemporizadorTeletransportacion, this, &AEnemigoSubterraneo::Teletransportar, 5.0f, true);
}

void AEnemigoSubterraneo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bEstaDetenido)
	{
		return;
	}

	// Definir el punto de inicio y fin del LineTrace
	FVector Inicio = GetActorLocation();
	FVector Fin = Inicio + (MovimientoDireccion * 100.0f); // 100 unidades delante del enemigo

	// Configurar los parámetros del LineTrace
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // Ignorar al propio enemigo

	// Realizar el LineTrace
	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Inicio, Fin, ECC_Visibility, Params);

	// Dibujar el LineTrace para depuración
	DrawDebugLine(GetWorld(), Inicio, Fin, FColor::Green, false, 1.0f, 0, 1.0f);

	if (bHit)
	{
		// Si se detecta un bloque, cambiar la dirección de movimiento al eje disponible
		if (MovimientoDireccion.X != 0.0f)
		{
			if (!HayObstaculoEnDireccion(FVector(0.0f, 1.0f, 0.0f)))
			{
				MovimientoDireccion = FVector(0.0f, 1.0f, 0.0f); // Cambiar al eje Y positivo
			}
			else if (!HayObstaculoEnDireccion(FVector(0.0f, -1.0f, 0.0f)))
			{
				MovimientoDireccion = FVector(0.0f, -1.0f, 0.0f); // Cambiar al eje Y negativo
			}
		}
		else
		{
			if (!HayObstaculoEnDireccion(FVector(1.0f, 0.0f, 0.0f)))
			{
				MovimientoDireccion = FVector(1.0f, 0.0f, 0.0f); // Cambiar al eje X positivo
			}
			else if (!HayObstaculoEnDireccion(FVector(-1.0f, 0.0f, 0.0f)))
			{
				MovimientoDireccion = FVector(-1.0f, 0.0f, 0.0f); // Cambiar al eje X negativo
			}
		}

		// Aplicar rotación
		FRotator NuevaRotacion = GetActorRotation();
		NuevaRotacion.Yaw += VelocidadRotacion * DeltaTime;
		SetActorRotation(NuevaRotacion);
	}

	// Mover al enemigo
	FVector NuevaPosicion = GetActorLocation() + (MovimientoDireccion * DeltaTime * 100.0f); // Ajustar la velocidad según sea necesario
	SetActorLocation(NuevaPosicion);
}

bool AEnemigoSubterraneo::HayObstaculoEnDireccion(FVector Direccion)
{
	// Definir el punto de inicio y fin del LineTrace
	FVector Inicio = GetActorLocation();
	FVector Fin = Inicio + (Direccion * 100.0f); // 100 unidades en la dirección dada

	// Configurar los parámetros del LineTrace
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // Ignorar al propio enemigo

	// Realizar el LineTrace
	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Inicio, Fin, ECC_Visibility, Params);

	// Dibujar el LineTrace para depuración
	DrawDebugLine(GetWorld(), Inicio, Fin, FColor::Red, false, 1.0f, 0, 1.0f);

	return bHit;
}

void AEnemigoSubterraneo::Teletransportar()
{
	// Buscar todos los actores de tipo bloque concreto en el mundo
	TArray<AActor*> BloquesConcretos;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABloqueConcreto::StaticClass(), BloquesConcretos);

	if (BloquesConcretos.Num() > 0)
	{
		// Seleccionar un bloque concreto aleatorio
		AActor* BloqueConcreto = BloquesConcretos[FMath::RandRange(0, BloquesConcretos.Num() - 1)];

		// Calcular la nueva posición a 1000 unidades de distancia del bloque concreto
		FVector NuevaPosicion = BloqueConcreto->GetActorLocation() + FVector(1000.0f, 0.0f, 0.0f);

		// Teletransportar al enemigo a la nueva posición
		SetActorLocation(NuevaPosicion);

		// Detener el movimiento del enemigo durante 5 segundos
		Detener();
		GetWorld()->GetTimerManager().SetTimer(TemporizadorDetencion, this, &AEnemigoSubterraneo::Reanudar, 1.0f, false);
	}
}

void AEnemigoSubterraneo::Detener()
{
	bEstaDetenido = true;
}

void AEnemigoSubterraneo::Reanudar()
{
	bEstaDetenido = false;
}


