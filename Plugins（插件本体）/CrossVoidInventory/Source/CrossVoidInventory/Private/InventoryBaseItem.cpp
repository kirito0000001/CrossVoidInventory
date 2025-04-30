#include "InventoryBaseItem.h"
#include "CP_Inventory.h"

UInventoryBaseItem::UInventoryBaseItem()
{
	ItemData.Time = FDateTime::Now();
	ROC_OnConstruct();
}

UInventoryBaseItem::~UInventoryBaseItem()
{
	OnItemRemove.Broadcast();
}

void UInventoryBaseItem::ChangeItemData()
{
	ROC_OnItemDataChanged();
	OnItemDataChanged.Broadcast();
}

void UInventoryBaseItem::DestroyItem()
{
	OnItemRemove.Broadcast();
	ConditionalBeginDestroy();
}

void UInventoryBaseItem::SetNewComponent(UCP_Inventory* NewComp)
{
	OwnerComponent->ItemDatas.Remove(this);
	OwnerComponent->OnInventoryDataRefresh.Broadcast();
	OwnerComponent = NewComp;
	NewComp->ItemDatas.Add(this);
	NewComp->OnInventoryDataRefresh.Broadcast();
}
