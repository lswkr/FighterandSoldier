#pragma once
//이거는 h파일만 있으므로 비주얼 스튜디오에서 생성

UENUM()
enum class EPracticeConfirmType : uint8  
{
	Yes,
	No
};

UENUM()
enum class EPracticeValidType : uint8 
{
	Valid,
	InValid
};

UENUM()
enum class EPracticeSuccessType : uint8
{
	Successful,
	Failed
};

UENUM(BlueprintType)
enum class EPracticeInputMode : uint8
{
	GameOnly,
	UIOnly
};

