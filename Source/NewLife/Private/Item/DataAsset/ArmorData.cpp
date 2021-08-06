// Made By Park Joo Hyeong. This is my first Portfollio.


#include "Item/DataAsset/ArmorData.h"
#include "BlueprintFunctionLibrary/MeshMergeFunctionLibrary.h"
#include "Singleton/ItemManagerSubsystem.h"

UArmorData::UArmorData()
{
	PrimaryAssetType = TEXT("Armor");
}

FGameplayTag UArmorData::GetItemTag()
{
	return ITEM_TAG_ARMOR;
}

USkeletalMesh* UArmorData::GetLoadedBody()
{	
	if (MergedBody == nullptr)
	{
		if(BodyPartsToLoad.Num() == 1)
		{
			MergedBody = BodyPartsToLoad[0].Get();
		}
		else
		{
			FSkeletalMeshMergeParams MeshMergeParams;

			int32 i = 0;

			for (auto BodyPart : BodyPartsToLoad)
			{
				USkeletalMesh* TmpMesh = BodyPart.Get();

				if (TmpMesh == nullptr)
				{
					TmpMesh = BodyPart.LoadSynchronous();
				}

				MeshMergeParams.MeshesToMerge.Emplace(TmpMesh);

				if (i != 0)
				{
					USkeleton* CriteriaSkeleton = BodyPartsToLoad[0].Get()->Skeleton;
					USkeleton* SkeletonToCompare = BodyPartsToLoad[i].Get()->Skeleton;

					if (CriteriaSkeleton != SkeletonToCompare)
					{
						return nullptr;
					}

					i++;
				}
			}

			MeshMergeParams.Skeleton = BodyPartsToLoad[0].Get()->Skeleton;
			MergedBody = UMeshMergeFunctionLibrary::MergeMeshes(MeshMergeParams);
		}		
	}

	return MergedBody;
}
