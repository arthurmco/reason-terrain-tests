/*
 * Represents a terrain square
 *
 * The terrain square is the basic unit of the game
 * It is, basically, a four-point object. This object has an unique terrain type
 *
 * It's more easy to represent this way in an editor.
 * You will be able to subdivide the block into more blocks, or join two equal blocks
 * into one.
 *
 * The smallest block you can have is a 1x1 terrain block, the value of a terrain unit
 * in the Familyline terrain file
 */
 type terrain_block = {
    x0: (int, int), /* top left */
    y0: (int, int), /* bottom left */
    x1: (int, int), /* top right */
    y1: (int, int), /* bottom right */

    terrainType: TerrainType.type_list
 };


/*
 *  Represents a map structure
 */
type map = {
    height: int,
    width: int,
    author: string,
    name: string,
    description: string,
};


let terrain = {
    name: "Test terrain", height: 640, width: 400, 
    author: "Test author", description: "Test terrain 123432"
};

Js.log("Name: " ++ terrain.name );
Js.log("Width: " ++ string_of_int(terrain.width) );
Js.log("Height: " ++ string_of_int(terrain.height) );