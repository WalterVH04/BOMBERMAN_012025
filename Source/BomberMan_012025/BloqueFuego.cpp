// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueFuego.h"

ABloqueFuego::ABloqueFuego()
{
    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse.M_Tech_Hex_Tile_Pulse'"));

        if (MaterialBase.Succeeded())
        {
            MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
        }
    }

	// Configuración del actor
    PrimaryActorTick.bCanEverTick = true; // Habilitar Tick()

    VelocidadRotacion = FRotator(0.0f, 100.0f, 0.0f); // Rotar en el eje Y a 100 grados por segundo
}

void ABloqueFuego::BeginPlay()
{
    Super::BeginPlay();
}

void ABloqueFuego::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Aplicar rotación
    AddActorLocalRotation(VelocidadRotacion * DeltaTime);
}