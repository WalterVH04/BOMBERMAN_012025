// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "EnemigoSubterraneo.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API AEnemigoSubterraneo : public AEnemigo
{
	GENERATED_BODY()

public:
	// Constructor
	AEnemigoSubterraneo();

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

	// Teletransportar al enemigo
	void Teletransportar();

	// Detener el movimiento del enemigo
	void Detener();

	// Reanudar el movimiento del enemigo
	void Reanudar();

	// Verificar si la posición está dentro de los límites del mapa


	// Temporizador para la teletransportación
	FTimerHandle TemporizadorTeletransportacion;

	// Temporizador para la detención
	FTimerHandle TemporizadorDetencion;

	// Bandera para indicar si el enemigo está detenido
	bool bEstaDetenido;

	// Límites del mapa
	FVector LimiteInferior;
	FVector LimiteSuperior;
};
