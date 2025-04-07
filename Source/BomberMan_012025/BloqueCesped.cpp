// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueCesped.h"

ABloqueCesped::ABloqueCesped()
{
    if (MallaBloque)
    {
        static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass'"));

        if (MaterialBase.Succeeded())
        {
            MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
        }
    }
    PrimaryActorTick.bCanEverTick = false;

    // Asegurar que la malla existe antes de modificarla
    if (MallaBloque)
    {
        MallaBloque->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Sin colisiones
    }
}