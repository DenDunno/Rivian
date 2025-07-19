#include "DirectionMovement.h"

UDirectionMovement::UDirectionMovement()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDirectionMovement::BeginPlay()
{
	Super::BeginPlay();
}

void UDirectionMovement::TickComponent(const float deltaTime, const ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);

	AActor* actor = GetOwner();

	const FVector current = actor->GetActorLocation();
	const FVector delta = MoveDirection.GetSafeNormal() * MoveSpeed * deltaTime;
	actor->SetActorLocation(current + delta);
	
	UE_LOG(LogTemp, Warning, TEXT("This is the data: %s"), *FString(Password));
}