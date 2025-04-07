// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueLadrillo.h"
//#include "Components/StaticMeshComponent.h"
//#include "Materials/MaterialInstanceDynamic.h"
//#include "Engine/Texture2D.h"


ABloqueLadrillo::ABloqueLadrillo()
{
    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Brick_Clay_New.M_Brick_Clay_New'"));
        if (MaterialBase.Succeeded())
        {
            MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
        }
    }

    // Configuración del actor
    PrimaryActorTick.bCanEverTick = true; // Habilitar el Tick()

    AmplitudMovimiento = 100.0f; // Distancia que se mueve a la izquierda y derecha
    VelocidadMovimiento = 2.0f; // Velocidad del movimiento
}

void ABloqueLadrillo::BeginPlay()
{
    Super::BeginPlay();
    PosicionInicial = GetActorLocation(); // Guardar la posición inicial
}

void ABloqueLadrillo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Movimiento en el eje Y adelante y atras
	float Desplazamiento = FMath::Cos(GetWorld()->GetTimeSeconds() * VelocidadMovimiento) * AmplitudMovimiento;
	FVector NuevaPosicion = PosicionInicial + FVector(0.0f, Desplazamiento, 0.0f);
	SetActorLocation(NuevaPosicion);
}