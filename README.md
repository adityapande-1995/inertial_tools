# Calculate inertial stats of a given model

## Build
To compile, source ignition installation first and then run:
```
mkdir build
cd build
cmake ; make
```

## Testing
To test the feature, run:
```
./build/total_mass test/model.sdf

Found trisphere_cycle model!

Found frame link in trisphere_cycle model!
Found fork link in trisphere_cycle model!
Found wheel_front link in trisphere_cycle model!
Found wheel_rear_left link in trisphere_cycle model!
Found wheel_rear_right link in trisphere_cycle model!
Total mass: 14.5

```

