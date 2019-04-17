open Reprocessing;

let xmax = 800;
let ymax = 800;
let max_fruit = 10;
let g = 0.2;

type coordinates2D = {
  x: float,
  y: float,
};

type fruit = {
  vector: coordinates2D,
  coordinate: coordinates2D,
  id_number: int,
};

type stateT = {
  fruit_img_src: array(imageT),
  list_of_fruits: list(fruit),
  background: imageT,
  bombImage: imageT,
};

let updateItem = item => {
  let coordinate = {
    x: item.coordinate.x +. item.vector.x,
    y: item.coordinate.y +. item.vector.y,
  };
  {...item, coordinate};
};

let setup = env => {
  Env.size(~width=xmax, ~height=ymax, env);
  let fruit_img_src = [|
    Draw.loadImage(~filename="./assets/apple_small.png", env),
    Draw.loadImage(~filename="./assets/banana_small.png", env),
    Draw.loadImage(~filename="./assets/coconut_small.png", env),
    Draw.loadImage(~filename="./assets/orange_small.png", env),
    Draw.loadImage(~filename="./assets/pineapple_small.png", env),
    Draw.loadImage(~filename="./assets/watermelon_small.png", env),
  |];
  {
    background: Draw.loadImage(~filename="./assets/background.png", env),
    list_of_fruits: [],
    bombImage: Draw.loadImage(~filename="assets/bomb_small.png", env),
    fruit_img_src,
    // fruits: [Fruit.initial(), Fruit.initial(), Fruit.initial()],
  };
};

let xDirection = () =>
  if (Random.int(2) >= 1) {
    0.0 -. Random.float(0.2);
  } else {
    0.0 +. Random.float(0.2);
  };

let yDirection = () => (-0.5) -. Random.float(0.5);

let initialDirection = () => {x: xDirection(), y: yDirection()};

let newFruit = () => {
  id_number: Random.int(6),
  vector: initialDirection(),
  coordinate: {
    x: Int32.to_float(Int32.of_int(xmax)) /. 2.,
    y: Int32.to_float(Int32.of_int(ymax)),
  },
};

let generateFruit = ({list_of_fruits}) =>
  if (List.length(list_of_fruits) < max_fruit) {
    [newFruit(), ...list_of_fruits];
  } else {
    list_of_fruits;
  };

let draw = (state, env) => {
  Draw.image(state.background, ~pos=(0, 0), ~width=xmax, ~height=ymax, env);
  let list_of_fruits = generateFruit(state);
  list_of_fruits
  |> List.iter(fruit =>
       Draw.subImagef(
         state.fruit_img_src[fruit.id_number],
         ~pos=(fruit.coordinate.x, fruit.coordinate.y),
         ~width=100.,
         ~height=100.,
         ~texPos=(0, 0),
         ~texWidth=100,
         ~texHeight=100,
         env,
       )
     );

  let state = {
    ...state,
    list_of_fruits: list_of_fruits |> List.map(updateItem),
  };
  state;
};

run(~setup, ~draw, ());