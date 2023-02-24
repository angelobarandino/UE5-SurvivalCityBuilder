// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/BTDecorator_CheckResourceStorage.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Inventory/SGInventoryComponent.h"

bool UBTDecorator_CheckResourceStorage::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
	{
		UObject* StorageObject = BlackboardComp->GetValueAsObject(StorageKey.SelectedKeyName);
		if (USGInventoryComponent* InventoryComp = Cast<USGInventoryComponent>(StorageObject))
		{
			TArray<TEnumAsByte<EResourceType>> ResoucesTypes;
			ResoucesTypes.Add(ResourceType);

			if (bAllResourceInStorage)
			{
				ResoucesTypes.Empty();
				InventoryComp->GetResourceTypesInStorage(ResoucesTypes);
			}


			EQuantityCondition Condition = QuantityCheckCondition.GetValue();
			for (const EResourceType Type : ResoucesTypes)
			{
				FSGResourceItem ResouceItem;
				if (InventoryComp->TryGetResource(Type, ResouceItem))
				{
					if (Condition == EQuantityCondition::NotEmpty && ResouceItem.Quantity <= 0)
					{
						return false;
					}

					if (Condition == EQuantityCondition::NotUnderMinQty && ResouceItem.Quantity < ResouceItem.MinQuantity)
					{
						return false;
					}
				}
			}
		}
	}

	return true;
}
