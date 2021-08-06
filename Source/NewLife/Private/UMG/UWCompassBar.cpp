// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWCompassBar.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

void UUWCompassBar::NativeConstruct()
{
	Super::NativeConstruct();
	
	UImage* CompassBar = Cast<UImage>(GetWidgetFromName("DSN_CompassBar"));
	
	if(CompassBar)
	{
		CompassMaterial = CompassBar->GetDynamicMaterial();
	}
}

void UUWCompassBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	const FRotator ControllerRotation = PlayerController->GetControlRotation();
		
	const float CompassRatio = ControllerRotation.Yaw / 360.f;
	
	CompassMaterial->SetScalarParameterValue("YawRatio", CompassRatio);
}
