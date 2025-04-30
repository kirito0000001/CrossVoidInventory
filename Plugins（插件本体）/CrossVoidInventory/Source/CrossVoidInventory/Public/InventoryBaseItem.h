#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PDA_InventoryType.h"
#include "InventoryBaseItem.generated.h"


class UCP_Inventory;

USTRUCT(BlueprintType)
struct FItemInformation
{
	GENERATED_BODY()
	//物品的基础信息
	//名称
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item", DisplayName="名称")
	FText Name;
	//介绍
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item", DisplayName="介绍", meta=(MultiLine=true))
	FText Description;
	//图标
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item", DisplayName="图标")
	UTexture2D* Icon;
	//类型
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item", DisplayName="类型")
	UPDA_InventoryType* Type;
	//数量
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item", DisplayName="数量")
	int Count;
	//堆叠数量
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item", DisplayName="堆叠数量")
	int MaxCount;
	//关键词
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item", DisplayName="关键词")
	TArray<FString> KeyWords;
	//物品的位置
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item", DisplayName="物品的位置")
	FIntPoint Location;

	//物品的额外属性
	//品质
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item|额外属性列表", DisplayName="品质")
	int Quality;
	//重量
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item|额外属性列表", DisplayName="重量")
	float Weight;
	//价格
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item|额外属性列表", DisplayName="价格")
	int Price;
	//耐久
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item|额外属性列表", DisplayName="耐久")
	int Durability;
	//等级
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item|额外属性列表", DisplayName="等级")
	int Level;
	//获取时间
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item|额外属性列表", DisplayName="获取时间")
	FDateTime Time;
	//优先级
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item|额外属性列表", DisplayName="优先级")
	int Priority;
	//页数
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item|额外属性列表", DisplayName="页数")
	int Pages;
	//相关物品
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item|额外属性列表", DisplayName="相关物品")
	TMap<TSubclassOf<UInventoryBaseItem>, FString> RelatedItem;
	//可拓展词条
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item|额外属性列表", DisplayName="可拓展词条")
	TArray<FString> ExtraAttributes;
	//额外介绍文本
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item|额外属性列表", DisplayName="额外介绍文本")
	TArray<FText> ExtraDescription;
};

UCLASS(Blueprintable)
class CROSSVOIDINVENTORY_API UInventoryBaseItem : public UObject
{
	GENERATED_BODY()

public:
	UInventoryBaseItem();
	~UInventoryBaseItem();

public:
	//委托
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FItemDelegaet);

	//物品数值改变时
	UPROPERTY(BlueprintAssignable, Category="Inventory|Item", DisplayName="物品数值改变时")
	FItemDelegaet OnItemDataChanged;

	//物品从背包物品移除/使用时
	UPROPERTY(BlueprintAssignable, Category="Inventory|Item", DisplayName="物品移除/使用时")
	FItemDelegaet OnItemRemove;

public:
	//事件函数
	//物品构造时
	UFUNCTION(BlueprintImplementableEvent, Category="Inventory|Item", DisplayName = "物品构造时")
	void ROC_OnConstruct();

	//物品数值改变时
	UFUNCTION(BlueprintImplementableEvent, Category="Inventory|Item", DisplayName = "物品数值改变时")
	void ROC_OnItemDataChanged();

	//物品使用时
	UFUNCTION(BlueprintImplementableEvent, Category="Inventory|Item", DisplayName = "物品使用时")
	void ROC_OnItemUse();

public:
	//手动触发改变物品数值委托
	UFUNCTION(BlueprintCallable, Category="Inventory|Item", DisplayName = "手动触发改变物品数值委托")
	void ChangeItemData();

	//手动触发物品摧毁时的委托
	UFUNCTION(BlueprintCallable, Category="Inventory|Item", DisplayName = "手动触发物品摧毁时的委托")
	void DestroyItem();

	//物品基础信息
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item", DisplayName="物品基础信息")
	FItemInformation ItemData;

	//父类组件
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inventory|Item", DisplayName="父类组件")
	UCP_Inventory* OwnerComponent;

	/**设置新的父类组件
	 * @param NewComp 新的父类组件
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory|Item", DisplayName = "设置新的父类组件")
	void SetNewComponent(UCP_Inventory* NewComp);
};
