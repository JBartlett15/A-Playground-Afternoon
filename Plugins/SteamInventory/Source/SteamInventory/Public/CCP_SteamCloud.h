// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "steam/steam_api.h"
#include "Misc/FileHelper.h"
#include "CCP_SteamCloud.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMINVENTORY_API UCCP_SteamCloud : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCCP_SteamCloud();

	UFUNCTION(BlueprintCallable, Category = "Steam")
	bool SaveToSteam(FString slotName);

	UFUNCTION(BlueprintCallable, Category = "Steam")
	bool LoadFromSteam(FString slotName);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
