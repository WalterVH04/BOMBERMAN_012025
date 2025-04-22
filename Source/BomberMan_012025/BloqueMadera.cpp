// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueMadera.h"
#include "TimerManager.h"

ABloqueMadera::ABloqueMadera()
{
    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Wood_Floor_Walnut_Polished.M_Wood_Floor_Walnut_Polished'"));

        if (MaterialBase.Succeeded())
        {
            MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0


        }
    }
}

void ABloqueMadera::BeginPlay()
{
    Super::BeginPlay();

    //desaparece alos 10 seg de estar espawneado
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABloqueMadera::AlternarVisibilidad, 10.0f, false);
    // Iniciar el timer para alternar visibilidad cada 2 segundos
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABloqueMadera::AlternarVisibilidad, 20.0f, true);
}
    
void ABloqueMadera::AlternarVisibilidad()
    {
        bEsVisible = !bEsVisible;

        SetActorHiddenInGame(!bEsVisible); // Ocultar o mostrar
        SetActorEnableCollision(bEsVisible); // Activar o desactivar colisiones
}