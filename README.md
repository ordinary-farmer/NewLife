# NewLife

Unreal Engine 4.26 Portfolio

------

프로젝트 버전 : 0.6v

[![NewLife Youtube Link](https://i.imgur.com/Z2lNU1u.png)](https://youtu.be/XLWDlVWetWY)

- 장르 : 3인칭 액션 게임
- 엔진버전 : Unreal Engine 4.26
- IDE : Rider for Unreal Engine 2021.1
- 작업 기간 : 두달 내외
- 영상 길이 : 4분 내외 (꼭 보시는 걸 추천합니다.)

- 본 프로젝트는 언리얼 엔진 코딩 스탠다드를 따릅니다.
- 언리얼 코딩 스탠다드 : (https://docs.unrealengine.com/4.27/ko/ProductionPipelines/DevelopmentSetup/CodingStandard/)

- 본 프로젝트의 애셋 이름은 이 링크의 명명 규칙을 따릅니다.
- 애셋 명명 규칙 : (https://github.com/ymkim50/ue4-style-guide/blob/master/README_Kor.md)



[TOC]



------

## Character Setting(AHero)

- UMG Class Diagram

![](https://i.imgur.com/cfg44XS.png)

------

### Modular Character

- 본 캐릭터는 5개의 파트로 구성된 모듈러 캐릭터입니다. 
  - Mesh : 캐릭터의 발
  - HeadMeshComp : 캐릭터의 머리
  - ShoulderMeshComp : 캐릭터의 어깨
  - ArmMeshComp : 캐릭터의 팔
  - TorsoMeshComp : 캐릭터의 가슴
  - MasterPoseComponent를 사용하여 Mesh를 부모로, 나머지를 Mesh의 자손으로 구성됩니다.

![](https://i.imgur.com/ZZ0F6DG.png)

- 문제는 사용해야할 Skeletal Mesh의 부분이 저렇게 딱 5개의 파트로 나눠지지 않았다는 점입니다.

![](https://i.imgur.com/gDmrJl3.png)

- 이 캐릭터의 머리부분을 만들기 위해 Eye, Head, Teeth, Beard를 합쳐야 하는데 이 부분은 스켈레탈 메시 병합을 이용해 해결했습니다.
- 이렇게 한 이유는 렌더링 비용 때문인데, 각 부분을 모두 USkeletalMeshComponent를 만들어서 사용하면 그 숫자만큼 드로우콜이 비례하기 때문입니다.
- 즉, 아주 작은 부분을 5개의 큰 부분으로 스켈레탈 메시병합을 하고 5개의 큰 부분은 MasterPoseComponent를 통해 메시들이 같은 애니메이션을 따르게 되는 것입니다.

```c++
void AHero::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
    // Merge seperated skeletal mesh parts of characters into 5 skeletal meshes...\
    // 디폴트 메시를 저장해놔야 디폴트 메시로 돌아와야 할 때 사용가능합니다.
    // 예: 아이템을 착용했다가 해제하는 경우
	TorsoMesh = MergeSkeletalMeshes(TorsoMeshMergeParam);
	HeadMesh = MergeSkeletalMeshes(HeadMeshMergeParam);
	ShoulderMesh = MergeSkeletalMeshes(ShoulderMeshMergeParam);
	LegMesh = MergeSkeletalMeshes(LegMeshMergeParam);
	ArmMesh = MergeSkeletalMeshes(ArmMeshMergeParam);
	
    // Set character's skeletal mesh components's mesh...
	GetMesh()->SetSkeletalMesh(LegMesh);
	HeadMeshComp->SetSkeletalMesh(HeadMesh);
	ShoulderMeshComp->SetSkeletalMesh(ShoulderMesh);
	ArmMeshComp->SetSkeletalMesh(ArmMesh);
	TorsoMeshComp->SetSkeletalMesh(TorsoMesh);
	
    // Set master pose component...
	HeadMeshComp->SetMasterPoseComponent(GetMesh());
	ShoulderMeshComp->SetMasterPoseComponent(GetMesh());
	ArmMeshComp->SetMasterPoseComponent(GetMesh());
	TorsoMeshComp->SetMasterPoseComponent(GetMesh());

    // ...
}

USkeletalMesh* AHero::MergeSkeletalMeshes(const FSkeletalMeshMergeParams& MeshMergeParams)
{
	if(MeshMergeParams.MeshesToMerge.Num() == 0)
	{
		return nullptr;
	}
	else if(MeshMergeParams.MeshesToMerge.Num() == 1)
	{
		return MeshMergeParams.MeshesToMerge[0];
	}

	USkeletalMesh* Result = UMeshMergeFunctionLibrary::MergeMeshes(MeshMergeParams);
	return Result;
}
```

<img src="https://i.imgur.com/W5FaGnQ.png" style="zoom:50%;" />

------

### AnimInstance and Foot IK Placement

- 캐릭터는 매 프레임마다 Locomotion 정보를 업데이트하고 이 정보에 따라 캐릭터가 움직이게 됩니다.

```c++
// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLocomotionInfo();

	TurnAndMove(DeltaTime);
}
void AHero::UpdateLocomotionInfo()
{
	LocomotionInfo.Speed = GetVelocity().Size();

	if (LocomotionInfo.Speed > 0.f)
	{
		LocomotionInfo.bIsMoving = true;
	}
	else
	{
		LocomotionInfo.bIsMoving = false;
	}

	LocomotionInfo.Acceleration = GetCharacterMovement()->GetCurrentAcceleration().Size();
	if (LocomotionInfo.Acceleration > 0.f)
	{
		LocomotionInfo.bIsAccelerating = true;
	}
	else
	{
		LocomotionInfo.bIsAccelerating = false;
	}

	LocomotionInfo.bIsInAir = GetCharacterMovement()->IsFalling();
	LocomotionInfo.bMoveInput = XInput != 0 || YInput != 0;
}

void AHero::TurnAndMove(float DeltaTime)
{
	const FRotator CameraWorldRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardBasedXInput(FRotationMatrix(CameraWorldRotation).GetScaledAxis(EAxis::X) * XInput);
	const FVector RightBasedYInput(FRotationMatrix(CameraWorldRotation).GetScaledAxis(EAxis::Y) * YInput);

	FVector DirectionToMove(ForwardBasedXInput + RightBasedYInput);
	DirectionToMove.Normalize();

	// Turn My Self
	if (LocomotionInfo.bIsMoving && LocomotionInfo.bMoveInput)
	{
		FRotator TurnTo;
		
		if(LocomotionInfo.bIsCarryingWeapon)
		{
			const FVector CameraForwardVector(FRotationMatrix(CameraWorldRotation).GetScaledAxis(EAxis::X));

			TurnTo = FRotator(FMath::RInterpTo(GetActorRotation(), CameraForwardVector.Rotation(), DeltaTime,
                                         HERO_TURN_RATE));
		}
		else
		{
			TurnTo = FRotator(FMath::RInterpTo(GetActorRotation(), DirectionToMove.Rotation(), DeltaTime,
                                         HERO_TURN_RATE));
		}

		TurnTo.Pitch = 0.f;
		SetActorRotation(TurnTo);
	}
	
	// Move My Self
	float MoveAmount;
	if (XInput == 0 || YInput == 0)
	{
		MoveAmount = FMath::Abs(XInput) + FMath::Abs(YInput);
	}
	else
	{
		MoveAmount = (FMath::Abs(XInput) + FMath::Abs(YInput)) / 2;
	}

	if(LocomotionInfo.bIsCarryingWeapon)
	{
		if(FVector::DotProduct(GetActorForwardVector(), DirectionToMove) < -0.01f)
		{
			MoveAmount *= .75f;
		}
		else
		{
			MoveAmount *= .9f;
		}
	}

	AddMovementInput(DirectionToMove, MoveAmount);
}
```

- 그리고 AnimInstance는 매 프레임마다 LocomotionInfo를 가져와서 애니메이션을 업데이트 합니다.
- AnimInstance는 private 멤버로 FootIKManager를 가지고 있는데 이 FootIKManager가 Foot Placement를 계산합니다.

```c++
/* UHeroAnimInstance */
class NEWLIFE_API UHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	// ...
    UPROPERTY()
	AHero* Owner;
    
    /* 유니크 포인터를 사용한 이유는 이때 당시 로직을 작성할 때 언리얼을 배운지 얼마 안되었고 */
    /* 직접 수명을 관리하고 싶어서 그랬습니다. */
	TUniquePtr<FHumanFootIKHelper> FootIKManager;
    
    // ...
}

/* FHumanFootIKHelper */
#pragma once

#include "CoreMinimal.h"
#include "HumanFootIkInfo.h"

#define LEFT_FOOT_SOCK_NAME (FName(TEXT("foot_l")))
#define RIGHT_FOOT_SOCK_NAME (FName(TEXT("foot_r")))
#define IK_FOOT_ROOT_SOCK_NAME (FName(TEXT("ik_foot_root")))

/**
* 인간형 캐릭터의 FootPlacement 계산을 도와주는 클래스입니다.
* 이 클래스를 사용하는 Mesh의 Skeleton은 반드시 "foot_l", "foot_r", "ik_foot_root"을 포함해야 합니다.
*/
class NEWLIFE_API FHumanFootIKHelper
{
public:
	FHumanFootIKHelper();
	virtual ~FHumanFootIKHelper();

	FHumanFootIKInfo UpdateFootIKInfo(UWorld* World, ACharacter* Character, FHumanFootIKInfo CurrentFootIKInfo,
	                                  float Deltatime);

private:
	FHumanFootIKInfo CalculateFootIKInterpolation(float DeltaTime, FHumanFootIKInfo CurrentFootIKInfo,
	                                              FHumanFootIKInfo DesiredFootIKInfo);

	static const float TraceDistanceFromFoot;
};
```

- UpdateFootIKInfo는 발 아래로 LineTrace를 해서 캐릭터의 양발 위치를 계산하고 발의 각도 또한 계산해줍니다. 
- 실직적인 계산은 전부 여기서 이루어지고 발이 순간이동하는 걸 원하지 않기 때문에 값을 보간하여 조금이라도 부드럽게 이동하게 해줍니다.

```c++
void UHeroAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
    
	//...
	// Place Foot By Using FFootIKHelper	
	if (!bIsInAir && !bIsMoving)
	{
		FootIKInfo = FootIKManager->UpdateFootIKInfo(GetWorld(), Owner, FootIKInfo, DeltaTime);
	}
	else
	{
		const FHumanFootIKInfo EmptyFootIKInfo;
		FootIKInfo = EmptyFootIKInfo;
	}
}
```

------

## Interact

### motivation

- 본 프로젝트의 상호작용은 어쌔신 크리드 오디세이에서 따왔습니다.(영상길이: 7초)

[![AC Odyssey Interact Example](https://i.imgur.com/SuaLXqs.png)](https://youtu.be/uo-lCeZwc_8)

- AC Odyssey Interact features
  - 어느 정도 가까이가면 물체를 인식함(인식 여부는 물체에 원 이미지를 띄움)
  - 더 가까이 가면 물체와 상호작용할 수 있음(상호작용 가능 여부는 겹쳐있는 두개의 원 이미지를 띄움)
  - 유저가 바라보는 방향에 따라 상호작용 우선순위가 바뀜
  - 물체마다 상호작용 텍스트 설정 가능함

### Interactable Actor UMG Diagram

![](https://i.imgur.com/dVTuQNW.png)

- AHero(본 프로젝트의 플레이어블 캐릭터)는 UInteractComponent를 들고 있고 이 컴포넌트가 IInteractable과의 상호작용을 담당합니다.

### UInteractComponent

- 가장 주목해서 볼 것은 RecognizedObjects와 InteractableObjects입니다.
- 이 두 컨테이너는 키(액터 이름)와 값(IInteractable*)을 가지는 TMap입니다.
  - RecognizedObjects : 내 캐릭터가 인식했지만 아직 상호작용할 수 없는 액터들의 정보를 담습니다.
  - InteractableObjects : 상호작용할 수 있는 액터들의 정보를 담습니다.

#### UInteractComponent의 기본 동작

- 캐릭터가 A라는 물체와 상호작용한다고 가정해보겠습니다.
  - 캐릭터는 A와의 거리가 어느정도 가까워지면 A를 인식하고 그 정보를 RecognizedObjects에 담습니다.
  - 캐릭터와 A와의 거리가 더 가까워지면 A를 RecognizedObjects에서 꺼내고 InteractableObjects에 담습니다.
  - InteractableObjects의 갯수가 0보다 크면 틱마다 상호작용 최우선순위 액터를 갱신합니다.
  - 캐릭터와 A가 상호작용하면 A는 단순히 자신을 비활성화합니다.
  - 캐릭터와 A가 어느정도 멀어지면 A를 InteractableObjects에서 꺼내고 RecognizedObjects에 담습니다.
  - 캐릭터와 A가 더 멀어지면 RecognizedObjects에서 A를 꺼냅니다.
- 상호작용 우선순위를 정할 때는 상호작용할 액터들의 ScreenLocation을 구한 다음, 뷰포트의 중앙점과의 거리를 비교하여 우선순위를 정하게 됩니다.

```c++
/* 틱마다 호출됩니다. */
void UInteractComponent::UpdateTopInteractableActor()
{
	if(InteractableObjects.Num() == 0)
	{
		return;
	}

	float MinDistance = TNumericLimits<float>::Max();

	FTopInteractive Tmp;

	for (auto& Elem : InteractableObjects)
	{
		if(Elem.Value->GetIsActive() == false)
		{
			continue;
		}
		
		FVector2D ElemScreenLocation;
		if (Elem.Value->TryGetScreenLocation(ElemScreenLocation))
		{
			const float DistanceBetween = FVector2D::Distance(ScreenCenterCoord, ElemScreenLocation);
			if (MinDistance > DistanceBetween)
			{
				MinDistance = DistanceBetween;
				Tmp.Interactive = Cast<IInteractable>(Elem.Value);
				Tmp.Key = Elem.Key;
			}
		}
	}
	
	if(TopInteractive.Interactive != nullptr)
	{
		TopInteractive.Interactive->ToggleInteractiveWidget(false);
	}
	
	if(Tmp.Interactive != nullptr)
	{
		Tmp.Interactive->ToggleInteractiveWidget(true);
		OwnerInteractHelperWidget->UpdateText(Tmp.Interactive->GetInteractText());
	}
	
	TopInteractive = Tmp;
}
```

### ABaseInteractive

![](https://i.imgur.com/VGFMyuF.png)

- 인식 범위와 상호작용 가능 범위는 ABaseInteractive.h에 정의해 두었습니다.

```c++
/* ABaseInteractive.h */

// 인식 범위
#define RECOGNITION_RANGE (800.f)

// ABaseInteractive 위에 띄워지는 원의 최대 높이
#define MAX_REACT_MARK_Z_LOCATION (270.f)

// 기본 Interaction Sphere의 반지름
#define DEFAULT_INTERACTION_SPHERE_RADIUS (32.f)

// 상호작용 가능 범위
#define INTERACTABLE_RANGE (100.f)
```

- Recognition Sphere와 Interaction Sphere의 반지름만 정해두면 되는거 아니냐고 물어보실 수 있는데 그렇게 한 이유는 물체의 크기는 가변적이기 때문입니다.
-  만약 Interaction Sphere의 반지름을 1미터로 정해두었는데 물체의 반지름이 1미터를 넘으면 어떻게 될까요?
- 이런 정의되지 않은 오류를 방지하기 위해 ABaseInteractive를 상속하는 클래스들은 Interaction Sphere의 반지름을 가변적으로 정하게 만들었습니다.

#### bAutoInteractionSphereRadius

- bAutoInteractionSphereRadius는 기본적으로 true이고, true면 OnConstruction()에서 Interaction Sphere의 반지름을 계산하여 정합니다.
- 반지름 계산 방법
  - 고려해야 할 것은 두가지 입니다.
    1. StaticMesh이든, SkeletalMesh이든 액터는 여러 Mesh들을 담고 있을 수 있다.
    2. 이 Mesh들은 반드시 액터 중앙에 위치한 것은 아니다.
  - 그렇기 때문에 Interaction Sphere의 반지름은 가장 먼 Mesh의 거리와 그 Mesh의 크기를 기준으로 상호작용 가능 범위를 더해서 정해집니다.
  - Recognition Sphere의 반지름은 인식 가능 범위로 정해집니다.
  - 예시 
    - 가장 멀리 떨어져 있는 메시는 원이고 중앙에서 1미터 떨어져 있습니다. 이 원의 크기는 30cm입니다. 
    - Interaction Sphere Radius = 100 + 30 + 100(상호작용 가능 범위)
    - Recognition Radius = 800(인식가능 범위)
    - Recognition Radius는 가변적이지 않은데 그 이유는 상호작용하는 물체가 너무 커지지 않길 원하기 때문입니다.
    - 하지만 이것은 정의되지 않은 오류가 생길 수 있기 때문에 개선해야할 사항이라고 보고 고쳐야 한다고 생각합니다.
  - 단, Z축의 거리는 고려하지 않고 X, Y에서의 거리만 고려합니다.

```c++
/* ABaseInteractive.cpp */
void ABaseInteractive::OnConstruction(const FTransform& Transform)
{
	FVector MyOrigin = RootComponent->GetComponentLocation();

	const float OriginZLocation = MyOrigin.Z;
	float MarkWidgetZLocation = 0;

	FVector OriginXY = MyOrigin;
	OriginXY.Z = 0.f;
	float InteractionSphereRadius = DEFAULT_INTERACTION_SPHERE_RADIUS;

    // 컴포넌트를 모두 가져와서 그 컴포넌트가 UPrimitiveComponent이고 충돌이 켜져있으면 
    // 그 컴포넌트의 정보는 Interaction Sphere Radius를 정하는데 사용됩니다.
	TArray<USceneComponent*> Components;
	RootComponent->GetChildrenComponents(true, Components);

	for (auto& Elem : Components)
	{
		UPrimitiveComponent* CollisionComponent = Cast<UPrimitiveComponent>(Elem);
        
		if (CollisionComponent && (CollisionComponent->GetCollisionEnabled() == ECollisionEnabled::Type::PhysicsOnly ||
			CollisionComponent->GetCollisionEnabled() == ECollisionEnabled::Type::QueryAndPhysics))
		{
			FVector ComponentLocation = CollisionComponent->GetComponentLocation();
			FVector ComponentBoxExtent = CollisionComponent->Bounds.BoxExtent;

			const float TmpZ = ComponentLocation.Z - OriginZLocation + ComponentBoxExtent.Z;
			if (TmpZ > MarkWidgetZLocation)
			{
				MarkWidgetZLocation = TmpZ;
			}

			if (bAutoInteractionSphereRadius == false)
			{
				continue;
			}

			if (ComponentLocation.X - OriginXY.X < 0.f)
			{
				ComponentBoxExtent.X *= -1.f;
			}

			if (ComponentLocation.Y - OriginXY.Y < 0.f)
			{
				ComponentBoxExtent.Y *= -1.f;
			}

			FVector Point1 = FVector(ComponentLocation.X + ComponentBoxExtent.X, ComponentLocation.Y, 0.f);
			FVector Point2 = FVector(ComponentLocation.X, ComponentLocation.Y + ComponentBoxExtent.Y, 0.f);
			FVector Point3 = FVector(ComponentLocation.X + ComponentBoxExtent.X,
			                         ComponentLocation.Y + ComponentBoxExtent.Y, 0.f);

			const float Distance1 = FVector::Distance(OriginXY, Point1);
			const float Distance2 = FVector::Distance(OriginXY, Point2);
			const float Distance3 = FVector::Distance(OriginXY, Point3);

			const float TmpRadius = FMath::Max3(Distance1, Distance2, Distance3);
			if (TmpRadius > InteractionSphereRadius)
			{
				InteractionSphereRadius = TmpRadius;
			}
		}
	}

	InteractionSphere->SetSphereRadius(InteractionSphereRadius + INTERACTABLE_RANGE);
	RecognitionSphere->SetSphereRadius(RECOGNITION_RANGE);

	MarkWidgetZLocation = FMath::Clamp(MarkWidgetZLocation, 0.f, MAX_REACT_MARK_Z_LOCATION);
	MarkWidget->SetRelativeLocation(FVector(0.f, 0.f, MarkWidgetZLocation));
}
```

- 결과물 영상(1분 내외)

[![AC Odyssey Interact Example](https://i.imgur.com/sFhHFJE.png)](https://youtu.be/4hcO5hMWUkk)

- 물론 경우에 따라 bAutoInteractionSphereRadius를 끌 수 있습니다.
- 본 포트폴리오 메인 영상에서 본 자동문은 bAutoInteractionSphereRadius가 꺼져있습니다. 켜면 InteractionSphere의 크기가 너무 커지기 때문입니다.

#### UInteractAttributeComponent

- 이 컴포넌트는 상호작용할 때 캐릭터가 재생해야할 몽타주, 소리, Effect를 가지고 있고 ABaseInteractive::OnInteract_Implementation(APawn*)에서 해당 애셋들을 사용합니다.

```c++
/* ABaseInteractive.cpp */
void ABaseInteractive::OnInteract_Implementation(APawn* PlayerPawn)
{
    // GenerateInteractionEffects에서 몽타주, 소리, ParticleSystem을 재생합니다.
	Attribute->GenerateInteractionEffects(PlayerPawn);
}
```

#### 쉬운 사용성

- BaseInteractive를 만들어 두었으니 상호작용 로직은 ABaseInteractive::OnInteract_Implementation(APawn*)을 override하여 정의합니다.
- 굳이 cpp로 작성할 필요가 없고 빠른 로직 작성을 원한다면 블루프린트가 유용하게 사용될 수 있습니다.
- 본 포트폴리오 영상 데모의 자동문과 꼬깔콘의 로직은 블루프린트로 작성되었습니다.

------

## Inventory

### ANLPlayerController

- 인벤토리는 ANLPlayerController를 구성하는 컴포넌트입니다.
- 인벤토리를 살펴보기 이전에 ANLPlayerController를 살펴볼 필요가 있습니다.
- ANLPlayerController는 APlayerController를 상속합니다.





