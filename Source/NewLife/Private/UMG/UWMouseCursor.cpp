// Made By Park Joo Hyeong. This is my first Portfollio.


#include "UMG/UWMouseCursor.h"
#include "Components/Image.h"

void UUWMouseCursor::SetCursorImage(UTexture2D* CursorTexture)
{
	CursorImage->SetBrushFromTexture(CursorTexture);
}
