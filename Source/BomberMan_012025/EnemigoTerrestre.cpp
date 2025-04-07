// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoTerrestre.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"

AEnemigoTerrestre::AEnemigoTerrestre()
{
	PrimaryActorTick.bCanEverTick = true;

	// acepta el evento de colisión
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemigoTerrestre::OnEnemigoHit);
}

void AEnemigoTerrestre::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemigoTerrestre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Movimiento simple en el eje X
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), DireccionMovimiento * VelocidadMovimiento * DeltaTime);
}

// Cambia la dirección del enemigo al chocar con otro objeto
void AEnemigoTerrestre::OnEnemigoHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	// Ignorar si se choca consigo mismo
	if (OtherActor && OtherActor != this && OtherComp)
	{
		// Cambiar dirección si choca con algo que no sea el jugador
		DireccionMovimiento *= -1;
	}
}