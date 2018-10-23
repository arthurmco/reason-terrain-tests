/* 
 * The map is a series of quadtree.
 * It can be a leaf node, or it can not.
 *
 * A leaf node have a terrain type, a non-leaf node has an array of 4 nodes.
 */
 type terrain_node_type = LeafNode(TerrainType.type_list) | NonLeafNode(array(terrain_block))

/*
 * Represents a terrain block
 *
 * The terrain square is the basic unit of the game
 * It is, basically, a quadtree
 * It's more easy to represent this way in an editor.
 *
 * The block can be subdivided in four pieces of equally-sized different blocks.
 * Since we assume they will always have the same size, we record only the height.
 *
 * The smallest block you can have is a 1x1 terrain block, the value of a terrain unit
 * in the Familyline terrain file
 */
and terrain_block = {
    heights: option((int, int, int, int)),
    blockType: terrain_node_type
}

/*
 * Receives a terrain block and divides it
 * 
 * The parent block type will be divided to all children block types.
 * The heights will also be calculated
 *
 * Returns the same block, with the children added
 */
let divide_block = (parent_block) => {

  let (a0, c0, c2, a2) = switch (parent_block.heights) {
    | Some(heights) => heights
    | None => (0, 0, 0, 0)
  };

  let a1 = (a2+a0)/2;
  let b0 = (c0+a0)/2;
  let c1 = (c2+c0)/2;
  let b1 = (c1+a1)/2;
  let b2 = (c2+a2)/2;

/*
          b0     c0
a0 +------+------+
   |      |      |
   |      |      |
   |    b1|      |
a1 *------+------+ c1
   |      |      |
   |      |      |
   |      |      |
a2 *------+------+ c2
          b2
*/

  let retchildren = [|
      {
          heights: Some((a0, b0, b1, a1)),
          blockType: parent_block.blockType 
      },
      {
          heights: Some((b0, c0, c1, b1)),
          blockType: parent_block.blockType
      },
      {
          heights: Some((b1, c1, c2, b2)),
          blockType: parent_block.blockType
      },
      {
          heights: Some((a1, b1, b2, a2)),
          blockType: parent_block.blockType
      }
    |];

  let ret = {
    heights: None,
    blockType: NonLeafNode(retchildren)
  };
  ret
};

 /*
  * Unites all children blocks of a specified block
  *
  * The heights will be recalculated based on the children heights
  * The terrain type will be the type of the top left child
  *
  * Returns the same block, with the children reunited
  */
let unite_children = (parent_block) => {
  let (a0, a2, c2, c0, btype) = switch(parent_block.blockType) {
    | LeafNode(_) => {
        let (a0, a2, c2, c0) = Belt.Option.mapWithDefault(parent_block.heights, (0, 0, 0, 0), ((t) => t));
        (a0, a2, c2, c0, parent_block.blockType);
      }
    | NonLeafNode(blocks) => {
        let (block_a0, _, _, _) = Belt.Option.mapWithDefault(blocks[0].heights, (0, 0, 0, 0), ((t) => t));
        let (_, block_a2, _, _) = Belt.Option.mapWithDefault(blocks[1].heights, (0, 0, 0, 0), ((t) => t));
        let (_, _, block_c2, _) = Belt.Option.mapWithDefault(blocks[2].heights, (0, 0, 0, 0), ((t) => t));
        let (_, _, _, block_c0) = Belt.Option.mapWithDefault(blocks[3].heights, (0, 0, 0, 0), ((t) => t));

        (block_a0, block_a2, block_c2, block_c0, blocks[0].blockType)
    }
  };

  let ret: terrain_block = {
    heights: Some((a0, a2, c2, c0)),
    blockType: btype
  };
  ret
};
