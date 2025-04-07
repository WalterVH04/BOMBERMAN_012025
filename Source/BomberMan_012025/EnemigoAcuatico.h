// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoAcuatico.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API AEnemigoAcuatico : public AEnemigo
{
	GENERATED_BODY()

public:
	// Constructor
	AEnemigoAcuatico();

protected:
	// Llamado cuando el juego comienza o cuando se genera
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemigo", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshEnemigo;
public:
	// Llamado cada cuadro
	virtual void Tick(float DeltaTime) override;

private:
	// Dirección de movimiento del enemigo
	FVector MovimientoDireccion;

	// Velocidad de rotación del enemigo
	float VelocidadRotacion;

	// Verificar si hay un obstáculo en la dirección dada
	bool HayObstaculoEnDireccion(FVector Direccion);

	// Obtener la dirección hacia el personaje principal
	FVector ObtenerDireccionHaciaPersonaje();
};
