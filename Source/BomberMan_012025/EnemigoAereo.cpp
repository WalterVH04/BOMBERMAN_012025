// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoAereo.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

AEnemigoAereo::AEnemigoAereo()
{
	PrimaryActorTick.bCanEverTick = true;

	if (MeshEnemigo)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Engine/VREditor/UI/ArrowMaterial.ArrowMaterial'"));

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

void AEnemigoAereo::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemigoAereo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Verificar si el personaje principal está mirando al enemigo
	if (EstaSiendoMiradoPorPersonaje())
	{
		// Detener el movimiento del enemigo
		bEstaDetenido = true;
		return;
	}
	else
	{
		// Reanudar el movimiento del enemigo
		bEstaDetenido = false;
	}

	if (bEstaDetenido)
	{
		return;
	}

	// Obtener la dirección hacia el personaje principal
	FVector DireccionHaciaPersonaje = ObtenerDireccionHaciaPersonaje();

	// Verificar si hay un obstáculo en la dirección hacia el personaje principal
	if (!HayObstaculoEnDireccion(DireccionHaciaPersonaje))
	{
		MovimientoDireccion = DireccionHaciaPersonaje;
	}
	else
	{
		// Definir el punto de inicio y fin del LineTrace
		FVector Inicio = GetActorLocation();
		FVector Fin = Inicio + (MovimientoDireccion * 700.0f); // 100 unidades delante del enemigo

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
	}

	// Mover al enemigo
	FVector NuevaPosicion = GetActorLocation() + (MovimientoDireccion * DeltaTime * 100.0f); // Ajustar la velocidad según sea necesario
	SetActorLocation(NuevaPosicion);
}

bool AEnemigoAereo::HayObstaculoEnDireccion(FVector Direccion)
{
	// Definir el punto de inicio y fin del LineTrace
	FVector Inicio = GetActorLocation();
	FVector Fin = Inicio + (Direccion * 700.0f); // 100 unidades en la dirección dada

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

FVector AEnemigoAereo::ObtenerDireccionHaciaPersonaje()
{
	// Obtener el personaje principal
	ACharacter* PersonajePrincipal = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PersonajePrincipal)
	{
		// Calcular la dirección hacia el personaje principal
		FVector Direccion = PersonajePrincipal->GetActorLocation() - GetActorLocation();
		Direccion.Z = 0.0f; // Ignorar la componente Z para movimiento en 2D
		Direccion.Normalize();
		return Direccion;
	}

	// Si no se encuentra el personaje principal, mantener la dirección actual
	return MovimientoDireccion;
}

bool AEnemigoAereo::EstaSiendoMiradoPorPersonaje()
{
	// Obtener el personaje principal
	ACharacter* PersonajePrincipal = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PersonajePrincipal)
	{
		// Definir el punto de inicio y fin del LineTrace
		FVector Inicio = PersonajePrincipal->GetActorLocation();
		FVector Fin = GetActorLocation();

		// Configurar los parámetros del LineTrace
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this); // Ignorar al propio enemigo
		Params.AddIgnoredActor(PersonajePrincipal); // Ignorar al personaje principal

		// Realizar el LineTrace
		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Inicio, Fin, ECC_Visibility, Params);

		// Dibujar el LineTrace para depuración
		DrawDebugLine(GetWorld(), Inicio, Fin, FColor::Blue, false, 1.0f, 0, 1.0f);

		return !bHit; // Si no hay obstáculos entre el personaje y el enemigo, el enemigo está siendo mirado
	}

	return false;
}

