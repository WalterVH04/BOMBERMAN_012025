// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bloque.h"
#include "BloqueLadrillo.generated.h"

/**
 *
 */
UCLASS()
class BOMBERMAN_012025_API ABloqueLadrillo : public ABloque
{
	GENERATED_BODY()
public:
	ABloqueLadrillo();

protected:

	virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
	FVector PosicionInicial; // Posición base del bloque
	float AmplitudMovimiento; // Cuánto se mueve a la izquierda y derecha
	float VelocidadMovimiento; // Qué tan rápido se mueve

};