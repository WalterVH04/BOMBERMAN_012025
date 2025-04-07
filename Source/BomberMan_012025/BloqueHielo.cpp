// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueHielo.h"
#include "TimerManager.h"

ABloqueHielo::ABloqueHielo()
{
	if (MallaBloque)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBase(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Water_Lake.M_Water_Lake'"));
		if (MaterialBase.Succeeded())
		{
			MallaBloque->SetMaterial(0, MaterialBase.Object); // Asignar el material al slot 0
		}
	}
	// Inicializar el bloque como visible
	PrimaryActorTick.bCanEverTick = false; // No necesita tick

	bEsVisible = true;
}

void ABloqueHielo::BeginPlay()
{
	Super::BeginPlay();

	// Iniciar el timer para alternar visibilidad cada 2 segundos
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABloqueHielo::AlternarVisibilidad, 2.0f, true);
}

void ABloqueHielo::AlternarVisibilidad()
{
	bEsVisible = !bEsVisible;

	SetActorHiddenInGame(!bEsVisible); // Ocultar o mostrar
	SetActorEnableCollision(bEsVisible); // Activar o desactivar colisiones
}