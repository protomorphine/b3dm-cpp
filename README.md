# b3dm-cpp  [![Continuous Integration](https://github.com/protomorphine/b3dm-cpp/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/protomorphine/b3dm-cpp/actions/workflows/ci.yml)
Provides API to work with `b3dm` [Cesium tiles format](https://github.com/CesiumGS/3d-tiles).   

# Usage
1. Read `b3dm` data:
```cpp
  auto file = std::make_unique<b3dm::streams::binary_file>("example.b3dm");

  b3dm::decoder const decoder(file.get());
  const b3dm::body& body = decoder.get_body();

  std::cout << "b3dm.body.feature_table_json = " << body.feature_table_json << '\n';
  std::cout << "b3dm.body.batch_table_json = " << body.batch_table_json << '\n';
```
2. Extract `glb` data in separate file:
```cpp
  auto file = std::make_unique<b3dm::streams::binary_file>("example.b3dm");

  b3dm::decoder decoder(file.get());
  const b3dm::body& body = decoder.get_body();

  std::cout << "b3dm contains " << body.gltf_data.size() << " gltf bytes\n";

  std::ofstream out_file("example.glb", std::ios::out | std::ios::binary | std::ios::app);
  out_file.write(decoder.get_body().gltf_data.data(), static_cast<std::streamoff>(body.gltf_data.size()));

  std::cout << out_file.tellp() << " bytes written\n";
```

Full API described in [documentation](https://protomorphine.github.io/b3dm-cpp)
# Building and installing

See the [BUILDING](BUILDING.md) document.

# Contributing

See the [CONTRIBUTING](CONTRIBUTING.md) document.

# Licensing

See [LICENSE](LICENSE) document.
