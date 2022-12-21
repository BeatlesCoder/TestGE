# TestGE

GameplayEffect Test

# Engine

Unreal Engine 5.1





Test effect "Per Rage Add 0.2% CriticalChance"  

_CriticalChance = CriticalChance + Rage * 0.2f;_

There are ETestType define in AMyCharacter.cs, 

```
enum class ETestType : uint8
{
   AttributeBase,
   GMMC,
   GEEC,
   OverrideGetter,
   PostAttributeChange,
};
```

**GMMC **and **AttributeBase** are almost identical in principle, while **GEEC** was dropped because it cannot be used for Infinite, **OverrideGetter** was dropped because it causes more complications, **PostAttributeChange** is available, but to listen for the application and removal of Effect requires more c++ code.

In summary Finally, you can use **AttributeBase**, **GMMC** and **PostAttributeChange** to implement them. When using AttributeBase and GMMC, you need to pay attention that the Setter method cannot be called in PostGameplayEffectExecute.

```
void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
   Super::PostGameplayEffectExecute(Data);
      /*
       * When using the AttributeBase approach,
       * calling SetCriticalChance() here will cause other GE's to modify CriticalChance incorrectly
       */
      // SetCriticalChance(FMath::Max(GetCriticalChance(), 0.0f));
}
```
