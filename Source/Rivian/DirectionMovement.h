// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DirectionMovement.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RIVIAN_API UDirectionMovement : public UActorComponent
{
	GENERATED_BODY()
public:	
	UDirectionMovement();
	UPROPERTY(EditAnywhere) FString	Password;
	UPROPERTY(EditAnywhere) FVector	MoveDirection;
	UPROPERTY(EditAnywhere) float MoveSpeed;
	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;
	
protected:
	virtual void BeginPlay() override;
};
