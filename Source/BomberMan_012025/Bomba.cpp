// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomba.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABomba::ABomba()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Malla de la bomba
    MallaBomba = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBloque"));
    //RootComponent = MeshComp;
    MallaBomba->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMallaBloque(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

    if (ObjetoMallaBloque.Succeeded())
    {
        MallaBomba->SetStaticMesh(ObjetoMallaBloque.Object);

        MallaBomba->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        MallaBomba->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
    }
	
}

// Called when the game starts or when spawned
void ABomba::BeginPlay()
{
	Super::BeginPlay();
	// Iniciar el timer para detonar la bomba
	GetWorld()->GetTimerManager().SetTimer(TimerHandleExplosion, this, &ABomba::Detonar, TiempoDetonacion, false);
}

// Called every frame
void ABomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomba::Detonar()
{
    FVector PosicionBomba = GetActorLocation();

    // Destruir bloques dentro del radio
    for (ABloque* Bloque : Bloques)
    {
        if (Bloque && FVector::Dist(Bloque->GetActorLocation(), PosicionBomba) <= RadioExplosion)
        {
            Bloque->Destroy();
        }
    }

    // Destruir enemigos dentro del radio
    for (AEnemigo* Enemigo : Enemigos)
    {
        if (Enemigo && FVector::Dist(Enemigo->GetActorLocation(), PosicionBomba) <= RadioExplosion)
        {
            Enemigo->Destroy();
        }
    }

    // Destruir la bomba después de explotar
    Destroy();
}