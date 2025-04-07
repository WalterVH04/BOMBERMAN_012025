// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bloque.h"
#include "BloqueFuego.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API ABloqueFuego : public ABloque
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	FRotator VelocidadRotacion; // Velocidad de rotación

public:
	// Constructor
	ABloqueFuego();	
};
