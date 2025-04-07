// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoTerrestre.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API AEnemigoTerrestre : public AEnemigo
{
	GENERATED_BODY()

public:
	// Constructor por defecto
	AEnemigoTerrestre();

protected:
	// Se llama cuando el juego comienza o cuando se genera el enemigo
	virtual void BeginPlay() override;

public:
	// Se llama cada frame
	virtual void Tick(float DeltaTime) override;

	// Evento de colisión
	UFUNCTION()
	void OnEnemigoHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

private:
	UPROPERTY(EditAnywhere, Category = "Movimiento")
	float VelocidadMovimiento = 100.0f;

	int32 DireccionMovimiento = 1;

};
