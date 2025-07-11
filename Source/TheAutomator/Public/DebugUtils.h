#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"

/** 
 * Print to screen. 
 * @param Duration - time in seconds 
 * @param Color - FColor for the text 
 * @param Format - printf‐style format string 
 * @param ... - printf‐style arguments 
 */
#define SCREEN_LOG(Duration, Color, Format, ...)                                \
do {																			\
if (GEngine)																	\
{																				\
GEngine->AddOnScreenDebugMessage(												\
-1, Duration, Color, FString::Printf(TEXT(Format), ##__VA_ARGS__)				\
);																				\
}																				\
} while (0)

/** 
 * Print to screen *and* to the UE log (Verbose). 
 */
#define DEBUG_LOG(Duration, Color, Format, ...)                                 \
do {																			\
UE_LOG(LogTemp, Verbose, TEXT(Format), ##__VA_ARGS__);							\
SCREEN_LOG(Duration, Color, Format, ##__VA_ARGS__);								\
} while (0)

/** 
 * Shortcut: red, 3 secs 
 */
#define SCREEN_ERROR(Format, ...)   SCREEN_LOG(3.f, FColor::Red, Format, ##__VA_ARGS__)
#define SCREEN_WARN(Format, ...)    SCREEN_LOG(3.f, FColor::Yellow, Format, ##__VA_ARGS__)
#define SCREEN_INFO(Format, ...)    SCREEN_LOG(3.f, FColor::White, Format, ##__VA_ARGS__)
#define DEBUG_ERROR(Format, ...)    DEBUG_LOG(3.f, FColor::Red, Format, ##__VA_ARGS__)
#define DEBUG_WARN(Format, ...)     DEBUG_LOG(3.f, FColor::Yellow, Format, ##__VA_ARGS__)
#define DEBUG_INFO(Format, ...)     DEBUG_LOG(3.f, FColor::White, Format, ##__VA_ARGS__)