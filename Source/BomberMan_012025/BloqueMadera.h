// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bloque.h"
#include "BloqueMadera.generated.h"

/**
 *
 */
UCLASS()
class BOMBERMAN_012025_API ABloqueMadera : public ABloque
{
	GENERATED_BODY()

public:
	ABloqueMadera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void AlternarVisibilidad(); // Método para ocultar y mostrar el bloque
	FTimerHandle TimerHandle; // Timer para controlar la visibilidad
	bool bEsVisible; // Estado de visibilidad
};