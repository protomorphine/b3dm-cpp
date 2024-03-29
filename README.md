# b3dm-cpp  
[![Continuous Integration](https://github.com/protomorphine/b3dm-cpp/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/protomorphine/b3dm-cpp/actions/workflows/ci.yml)  
Provides API to work with `b3dm` [Cesium tiles format](https://github.com/CesiumGS/3d-tiles).   

# Usage
1. Read `b3dm` data:
```cpp
  std::ifstream b3dm_file("example.b3dm", std::ios::binary);
  b3dm::streams::BinaryFile stream(b3dm_file);

  b3dm::Decoder const decoder(stream);
  const auto& body = decoder.GetBody();

  std::cout << "b3dm.body.FeatureTableJson = " << body.FeatureTableJson << '\n';
  std::cout << "b3dm.body.BatchTableJson = " << body.BatchTableJson << '\n';
```
2. Extract `glb` data in separate file:
```cpp
  std::ifstream b3dm_file("example.b3dm", std::ios::binary);
  b3dm::streams::BinaryFile stream(b3dm_file);

  b3dm::Decoder const decoder(stream);
  const auto& body = decoder.GetBody();

  std::cout << "b3dm contains " << body.GlbData.size() << " gltf bytes\n";

  std::ofstream out_file("example.glb", std::ios::out | std::ios::binary | std::ios::app);
  out_file.write(decoder.GetBody().GlbData.data(), static_cast<std::streamoff>(body.GlbData.size()));

  std::cout << out_file.tellp() << " bytes written\n";
```

Full API described in [documentation](https://protomorphine.github.io/b3dm-cpp)
# Building and installing

See the [BUILDING](BUILDING.md) document.

# Contributing

See the [CONTRIBUTING](CONTRIBUTING.md) document.

# Licensing

See [LICENSE](LICENSE) document.
