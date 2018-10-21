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
 * The parent block type will be divided to all children
 * block types.
 * The heights will also be calculated
 *
 * Returns the same block, with the children added
 */
 let divide_block = (_parent_block) => {

    _parent_block;
 };

 /*
  * Unites all children blocks of a specified block
  *
  * The heights will be recalculated based on the children heights
  * The terrain type will be the type of the top left child
  *
  * Returns the same block, with the children reunited
  */
let unite_children = (_parent_block) => {

    _parent_block
}
