// Fill out your copyright notice in the Description page of Project Settings.


#include "CCP_SteamInventory.h"
#include "Async/Async.h"

// Sets default values for this component's properties
UCCP_SteamInventory::UCCP_SteamInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCCP_SteamInventory::RefreshInventory()
{
	SteamInventoryResult_t result;
	if (SteamAPI_Init() && SteamInventory()) {

		//Get all items and return them
		if (SteamInventory()->GetAllItems(&result)) {
			inventoryResultCallBack.Set(result, this, &UCCP_SteamInventory::OnInventoryResult);
			
		}
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("No inventory or steam api"));
	}
}

void UCCP_SteamInventory::DropItem(int32 ID)
{
	if (!SteamInventory()) {
		UE_LOG(LogTemp, Warning, TEXT("Steam Inventory not available."));
		return;
	}

	SteamInventoryResult_t result;

	if (SteamInventory()->TriggerItemDrop(&result, (SteamItemDef_t)ID)) {
		UE_LOG(LogTemp, Log, TEXT("Steam Loot Drop Triggered for Generator: %d"), ID);
		inventoryResultCallBack.Set(result, this, &UCCP_SteamInventory::OnInventoryResult);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Failed to trigger Steam Loot Drop. Check AppID and ItemDefID."));
	}
}

void UCCP_SteamInventory::ManualGrantItem(int32 id, int32 amount)
{
	if (!SteamInventory()) {
		return;
	}

	SteamInventoryResult_t result;

	SteamItemDef_t itemDefs[1] = { (SteamItemDef_t)id };
	uint32 quant[1] = { (uint32)amount };

	if (SteamInventory()->GenerateItems(&result, itemDefs, quant, 1)) {
		inventoryResultCallBack.Set(result, this, &UCCP_SteamInventory::OnInventoryResult);

	}
}

void UCCP_SteamInventory::OnInventoryResult(SteamInventoryResultReady_t* callBack, bool IOFail)
{
	//Both need to come back OK
	bool successful = (!IOFail && callBack->m_result == k_EResultOK);
	TArray<FSteamInventoryItem> itemOutput;

	if (successful) {
		uint32 itemCount = 0;
		if (SteamInventory()->GetResultItems(callBack->m_handle, nullptr, &itemCount)) {
			TArray<SteamItemDetails_t> steamItems;
			steamItems.SetNum(itemCount);
			SteamInventory()->GetResultItems(callBack->m_handle, steamItems.GetData(), &itemCount);

			for (uint32 i = 0; i < itemCount; i++) {
				FSteamInventoryItem newItem;
				newItem.itemDefinition = steamItems[i].m_iDefinition;
				newItem.quantity = steamItems[i].m_unQuantity;
				newItem.itemId = steamItems[i].m_itemId;
				itemOutput.Add(newItem);
			}

		}
	}
	else {
		AsyncTask(ENamedThreads::GameThread, [this, itemOutput]() {
			TArray<FSteamInventoryItem> empty;
			onInventoryReady.Broadcast(false, empty);
			});
	}
	//close the connection/clean up
	SteamInventory()->DestroyResult(callBack->m_handle);

	//Broadcast on the game thread
	AsyncTask(ENamedThreads::GameThread, [this, successful, itemOutput]() {
		onInventoryReady.Broadcast(successful, itemOutput);
	});
}


// Called when the game starts
void UCCP_SteamInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCCP_SteamInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

