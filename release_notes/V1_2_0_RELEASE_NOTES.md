# SBK_Button 1.2.0

Version 1.2.0 adds caller-supplied timing for workflows that synchronize multiple components during one loop iteration.

## Added

- A new `update(uint32_t now)` overload that uses a supplied millisecond timestamp for debouncing, press and release durations, and long-press detection.
- Documentation showing how to read `millis()` once and share that value across a larger workflow.

```cpp
void loop()
{
    uint32_t now = millis();
    button.update(now);
    // Update other components using the same value of now.
}
```

The existing parameterless `update()` method remains fully compatible and delegates to `update(millis())`.
