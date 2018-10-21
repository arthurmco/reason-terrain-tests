let terrain = TerrainMap.{
    name: "Test terrain", height: 640, width: 400, 
    author: "Test author", description: "Test terrain 123432",
    main_block: Terrain.{
        heights: Some((0, 0, 0, 0)), 
        blockType: Terrain.LeafNode(TerrainType.Grass)
    }
};

Js.log("Name: " ++ terrain.name );
Js.log("Width: " ++ string_of_int(terrain.width) );
Js.log("Height: " ++ string_of_int(terrain.height) );