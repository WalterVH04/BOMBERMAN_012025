// Copyright Epic Games, Inc. All Rights Reserved.

#include "BomberMan_012025GameMode.h"
#include "BomberMan_012025Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Bloque.h"
#include "BloqueAcero.h"
#include "BloqueConcreto.h"
#include "BloqueLadrillo.h"
#include "BloqueMadera.h"
#include "BloqueBurbuja.h"
#include "BloqueHielo.h"
#include "BloqueVidrio.h"
#include "BloqueSline.h"
#include "BloqueFuego.h"
#include "BloqueCesped.h"
#include "Enemigo.h"
#include "EnemigoTerrestre.h"
#include "EnemigoAcuatico.h"
#include "EnemigoAereo.h"
#include "EnemigoSubterraneo.h"

ABomberMan_012025GameMode::ABomberMan_012025GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABomberMan_012025GameMode::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Red, TEXT("Bloque Spawning"));

	// Recorremos la matriz para generar los bloques
	for (int32 fila = 0; fila < aMapaBloques.Num(); ++fila)
	{
		for (int32 columna = 0; columna < aMapaBloques[fila].Num(); ++columna)
		{
			int32 valor = aMapaBloques[fila][columna];
			if (valor != 0) // Si no es espacio vacío
			{
				// Calculamos la posición del bloque
				FVector posicionBloque = FVector(
					XInicial + columna * AnchoBloque,
					YInicial + fila * LargoBloque,
					0.0f); // Z queda en 0 (altura del bloque)

				// Llamamos a la función para generar un bloque
				SpawnBloque(posicionBloque, valor);
			}
		}
	}
	//GetWorld()->GetTimerManager().SetTimer(tHDestruirBloques, this, &ABomberMan_012025GameMode::DestruirBloque, 2.0f, true);
	GetWorld()->GetTimerManager().SetTimer(tHDestruirBloques, this, &ABomberMan_012025GameMode::DestruirBloqueBurbuja, 1.0f, true);

	GetWorld()->GetTimerManager().SetTimer(tHDestruirEnemigos, this, &ABomberMan_012025GameMode::DestruirEnemigos, 3.0f, true);
}

// Función para generar un bloque
void ABomberMan_012025GameMode::SpawnBloque(FVector posicionBloque, int32 tipoBloque)
{
	//ABloque* BloqueGenerado = nullptr;
	ABloque* BloqueGenerado = nullptr;

	//le damos un valor por defecto a la variable BloqueGenerado
	ACharacter* CharacterGenerado = nullptr;

	// Elegir tipo de bloque basado en el valor

	if (tipoBloque == 1)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueAcero>(ABloqueAcero::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 2)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueConcreto>(ABloqueConcreto::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 3)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueLadrillo>(ABloqueLadrillo::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 4)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueMadera>(ABloqueMadera::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 5)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueBurbuja>(ABloqueBurbuja::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 6)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueHielo>(ABloqueHielo::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 7)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueVidrio>(ABloqueVidrio::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 8)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueSline>(ABloqueSline::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 9)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueFuego>(ABloqueFuego::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 10)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueCesped>(ABloqueCesped::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 11)
	{
		CharacterGenerado = GetWorld()->SpawnActor<AEnemigoTerrestre>(AEnemigoTerrestre::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 12)
	{
		CharacterGenerado = GetWorld()->SpawnActor<AEnemigoAereo>(AEnemigoAereo::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 13)
	{
		CharacterGenerado = GetWorld()->SpawnActor<AEnemigoAcuatico>(AEnemigoAcuatico::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 14)
	{
		CharacterGenerado = GetWorld()->SpawnActor<AEnemigoSubterraneo>(AEnemigoSubterraneo::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else {
		return;
	}
	// Agregar el bloque al TArray si fue generado
	if (BloqueGenerado)
	{
		aBloques.Add(BloqueGenerado);
	}

}

/*void ABomberMan_012025GameMode::DestruirBloque()
{
	//Seleccionar aleatoriamente un bloque del array ABloques para su eliminacion
	int numeroBloques = aBloques.Num();
	int NumeroAleatorio = FMath::RandRange(1, numeroBloques);

	if (aBloques.Num() > 0)
	{
		BloqueActual = aBloques[NumeroAleatorio]; // Obtén el primer bloque
		if (BloqueActual)
		{
			BloqueActual->Destroy();
			// Realiza operaciones con el bloque
			//primerBloque->SetActorLocation(FVector(100.0f, 100.0f, 100.0f));
		}
	}
}*/  //HASTA AQUI ES TODOOOO...

//para destruir bloqueburbuja con el tarray de bloque
void ABomberMan_012025GameMode::DestruirBloqueBurbuja()
{
	//Seleccionar aleatoriamente un bloque del array ABloques para su eliminacion
	int numeroBloques = aBloques.Num();
	int NumeroAleatorio = FMath::RandRange(1, numeroBloques);
	if (aBloques.Num() > 0)
	{
	ABloqueBurbuja* BloqueBurbuja = Cast<ABloqueBurbuja>(aBloques[NumeroAleatorio]); // Obtén el primer bloque
	if (BloqueBurbuja)
{
				BloqueBurbuja->Destroy();
				// Realiza operaciones con el bloque
				//primerBloque->SetActorLocation(FVector(100.0f, 100.0f, 100.0f));

			}
		}
}

//para destruir a los enemigos con el tarray de enemigos
void ABomberMan_012025GameMode::DestruirEnemigos()
{
	//Seleccionar aleatoriamente un enemigo del array AEnemigo para su eliminacion
	int numeroEnemigos = aEnemigos.Num();
	int NumeroAleatorio = FMath::RandRange(1, numeroEnemigos);
	if (aEnemigos.Num() > 0)
	{
		AEnemigo* Enemigo = Cast<AEnemigo>(aEnemigos[NumeroAleatorio]); // Obtén el primer enemigo
		if (Enemigo)
		{
			Enemigo->Destroy();
			// Realiza operaciones con el enemigo
			//primerBloque->SetActorLocation(FVector(100.0f, 100.0f, 100.0f));
		}
	}
}

//quiero que spawnee los enemigos aereos 44444444444
void ABomberMan_012025GameMode::SpawnEnemigoAereo()
{
	// Definir la posición de spawn
	FVector PosicionSpawn = FVector(400.0f, 2000.0f, 300.0f); // posición deseada
	// Hacer spawn del enemigo aéreo
	AEnemigoAereo* EnemigoAereo = GetWorld()->SpawnActor<AEnemigoAereo>(AEnemigoAereo::StaticClass(), PosicionSpawn, FRotator(0.0f, 0.0f, 0.0f));
	if (EnemigoAereo)
	{
		aEnemigos.Add(EnemigoAereo);
	}
}

/*
void AMyActor::TestMap()
{
	// Crear el TMap
	TMap<FString, int32> ExampleMap;

	// Agregar elementos
	ExampleMap.Add("Jugador1", 100);
	ExampleMap.Add("Jugador2", 200);
	ExampleMap.Add("Jugador3", 300);

	// Acceder a un valor
	if (int32* Score = ExampleMap.Find("Jugador2"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Puntuación de Jugador2: %d"), *Score);
	}

	// Eliminar un elemento
	ExampleMap.Remove("Jugador1");

	// Iterar sobre el TMap
	for (const TPair<FString, int32>& Pair : ExampleMap)
	{
		UE_LOG(LogTemp, Warning, TEXT("Clave: %s, Valor: %d"), *Pair.Key, Pair.Value);
	}
}
*/


// Create a new Enemigo
//ABloque* bloque01 = GetWorld()->SpawnActor<ABloque>(ABloque::StaticClass(), FVector(934.0f, 1370.0f, 100.0f), FRotator(0.0f, 0.0f, 0.0f));
//ABloque* bloque02 = GetWorld()->SpawnActor<ABloque>(ABloque::StaticClass(), FVector(734.0f, 1370.0f, 50.0f), FRotator(0.0f, 0.0f, 0.0f));

//int numeroBloqueConMovimiento = 0;

/*
for (int i = 0; i < 20; i++)
{

	ABloque* bloque = GetWorld()->SpawnActor<ABloque>(ABloque::StaticClass(), FVector(500.0f + i * 100 , 2500.0f - i * 100, 20.0f), FRotator(0.0f, 0.0f, 0.0f));


	if (bloque->bPuedeMoverse)
	{
		numeroBloqueConMovimiento++;
	}

	if (numeroBloqueConMovimiento >= 6)
	{
		bloque->bPuedeMoverse = false;
	}

}
*/
//SpawnBloques();


/*
void ABomberMan_012025GameMode::SpawnBloques()
{
	// recorrer el array de bloques y hacer spawn de cada uno
	for (int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if (aMapaBloques[i][j] == 1)
			{
				FVector PosicionBloque = FVector()
				ABloqueLadrillo* BloqueLadrillo = GetWorld()->SpawnActor<ABloqueLadrillo>(ABloqueLadrillo::StaticClass(), FVector(posicionSiguienteBloque.X + j * AnchoBloque, posicionSiguienteBloque.Y - i * LargoBloque, posicionSiguienteBloque.Z), FRotator(0.0f, 0.0f, 0.0f));
		*/		/*if (BloqueLadrillo)
				{
					aBloques.Add(static_cast<ABloque*>(BloqueLadrillo));
				}*/
				/*		}
					}
					//ABloque* bloque = GetWorld()->SpawnActor<ABloque>(ABloque::StaticClass(), FVector(500.0f + i * 100, 2500.0f - i * 100, 20.0f), FRotator(0.0f, 0.0f, 0.0f));
				}
			}
			*/