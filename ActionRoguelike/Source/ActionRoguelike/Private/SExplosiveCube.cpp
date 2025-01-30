// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveCube.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveCube::ASExplosiveCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("Radial Force Component");
	ForceComp->Radius = 500.0f;
	ForceComp->ImpulseStrength = 3000.0f;
	ForceComp->bImpulseVelChange = true;

    //CubeMesh->SetSimulatePhysics(true);
    //CubeMesh->SetNotifyRigidBodyCollision(true);
	//CubeMesh->OnComponentHit.AddDynamic(this, &ASExplosiveCube::MyHitCallbackFunction);
}

// Called when the game starts or when spawned
void ASExplosiveCube::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASExplosiveCube::MyHitCallbackFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || !OtherComp) return;

	ForceComp->FireImpulse();
}

// Called every frame
void ASExplosiveCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

