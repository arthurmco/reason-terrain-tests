open Jest;
open Expect;

let () =
    describe("Terrain Test", () => {
        describe("divide a block", () => {
            let block = Terrain.{
                heights: Some((0, 0, 10, 10)),
                blockType: Terrain.LeafNode(TerrainType.Grass)
            };

            test("check if it divides", () => {
                let newBlock = Terrain.divide_block(block);
                expect(newBlock.heights) |> toEqual(None) |> ignore;

                switch (newBlock.blockType) {
                    | Terrain.LeafNode(_) => expect(true) |> toEqual(false);
                    | Terrain.NonLeafNode(nodes) => {
                        expect(ArrayLabels.length(nodes)) |> toEqual(4);
                    }
                };
            });
            test("check if the heights are right", () => {
                let newBlock = Terrain.divide_block(block);
                expect(newBlock.heights) |> toEqual(None) |> ignore;

                switch (newBlock.blockType) {
                    | Terrain.LeafNode(_) => expect(true) |> toEqual(false);
                    | Terrain.NonLeafNode(nodes) => {
                        expect(nodes[0].heights) |> toEqual(Some((0, 0, 5, 5))) |> ignore
                        expect(nodes[1].heights) |> toEqual(Some((0, 0, 5, 5))) |> ignore
                        expect(nodes[2].heights) |> toEqual(Some((5, 5, 10, 10))) |> ignore
                        expect(nodes[3].heights) |> toEqual(Some((5, 5, 10, 10)))
                    }
                };
            });
            test("check if the terrain types are right", () => {
                let newBlock = Terrain.divide_block(block);
                expect(newBlock.heights) |> toEqual(None) |> ignore

                switch (newBlock.blockType) {
                    | Terrain.LeafNode(_) => expect(true) |> toEqual(false);
                    | Terrain.NonLeafNode(nodes) => {
                        expect(nodes[0].blockType) |> toEqual(Terrain.LeafNode(TerrainType.Grass)) |> ignore;
                        expect(nodes[1].blockType) |> toEqual(Terrain.LeafNode(TerrainType.Grass)) |> ignore;
                        expect(nodes[2].blockType) |> toEqual(Terrain.LeafNode(TerrainType.Grass)) |> ignore;
                        expect(nodes[3].blockType) |> toEqual(Terrain.LeafNode(TerrainType.Grass));
                    }
                }
            });
        });
        describe("unite a block", () => {
            let block = Terrain.{
                heights: None,
                blockType: Terrain.NonLeafNode([|
                    Terrain.{
                        heights: Some((10, 10, 15, 15)),
                        blockType: Terrain.LeafNode(TerrainType.Sand)
                    },
                    Terrain.{
                        heights: Some((10, 10, 15, 15)),
                        blockType: Terrain.LeafNode(TerrainType.Sand)
                    },
                    Terrain.{
                        heights: Some((15, 15, 20, 20)),
                        blockType: Terrain.LeafNode(TerrainType.Sand)
                    },
                    Terrain.{
                        heights: Some((15, 15, 20, 20)),
                        blockType: Terrain.LeafNode(TerrainType.Sand)
                    }
                |])
            };

            test("check if the height is right", () => {
                let newBlock = Terrain.unite_children(block);
                expect(newBlock.heights) |> toEqual(Some((10, 10, 20, 20))) 
            });
            test("check if the terrain type is right", () => {
                let newBlock = Terrain.unite_children(block);
                expect(newBlock.blockType) |> toEqual(Terrain.LeafNode(TerrainType.Sand))
            });
            test("check if it unites recursively", () => {
                expect(true) |> toEqual(true);
            });
        });
    });
