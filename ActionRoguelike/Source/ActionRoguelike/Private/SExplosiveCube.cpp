// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveCube.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASExplosiveCube::ASExplosiveCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("Radial Force Component");
	ForceComp->SetupAttachment(MeshComp);

	ForceComp->SetAutoActivate(false);
	ForceComp->Radius = 500.0f;
	ForceComp->ImpulseStrength = 2500.0f;
	ForceComp->bImpulseVelChange = true;

	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveCube::OnActorHit);
}

// Called when the game starts or when spawned
void ASExplosiveCube::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASExplosiveCube::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || !OtherComp) return;

	ForceComp->FireImpulse();

	// Log, Error, Warning
	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Cube"));

	UE_LOG(LogTemp, Warning, TEXT("Other Actor: %s at time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at locations: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}

// Called every frame
void ASExplosiveCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}