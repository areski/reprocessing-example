open Reprocessing;

let xmax = 800;
let ymax = 800;
let g = 0.2;

type coordinates2D = {
  x: float,
  y: float,
};

type fruit = {
  vector: coordinates2D,
  coordinate: coordinates2D,
  fruit_number: int,
};

type stateT = {
  fruit_images: array(imageT),
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
  let fruit_images = [|
    Draw.loadImage(~filename="./assets/apple_small.png", env),
    Draw.loadImage(~filename="./assets/banana_small.png", env),
    Draw.loadImage(~filename="./assets/coconut_small.png", env),
    Draw.loadImage(~filename="./assets/orange_small.png", env),
    Draw.loadImage(~filename="./assets/pineapple_small.png", env),
    Draw.loadImage(~filename="./assets/watermelon_small.png", env),
  |];
  {
    background: Draw.loadImage(~filename="./assets/background.png", env),
    list_of_fruits: [
      {
        fruit_number: Random.int(6),
        vector: {
          x: 0.1,
          y: 0.2,
        },
        coordinate: {
          x: 0.0,
          y: 700.0,
        },
      },
      {
        fruit_number: Random.int(6),
        vector: {
          x: 0.5,
          y: 0.1,
        },
        coordinate: {
          x: 10.0,
          y: 200.0,
        },
      },
      {
        fruit_number: Random.int(6),
        vector: {
          x: 1.0,
          y: 0.3,
        },
        coordinate: {
          x: 190.0,
          y: 0.0,
        },
      },
      {
        fruit_number: Random.int(6),
        vector: {
          x: 0.5,
          y: 0.5,
        },
        coordinate: {
          x: 0.0,
          y: 200.0,
        },
      },
      {
        fruit_number: Random.int(6),
        vector: {
          x: 0.5,
          y: 0.5,
        },
        coordinate: {
          x: 0.0,
          y: 50.0,
        },
      },
      {
        fruit_number: Random.int(6),
        vector: {
          x: 0.2,
          y: 0.5,
        },
        coordinate: {
          x: 20.0,
          y: 0.0,
        },
      },
      {
        fruit_number: Random.int(6),
        vector: {
          x: (-0.5),
          y: (-0.5),
        },
        coordinate: {
          x: 1000.0,
          y: 1000.0,
        },
      },
      {
        fruit_number: Random.int(6),
        vector: {
          x: (-0.5),
          y: (-0.5),
        },
        coordinate: {
          x: 0.0,
          y: 400.0,
        },
      },
    ],
    bombImage: Draw.loadImage(~filename="assets/bomb_small.png", env),
    fruit_images,
    // fruits: [Fruit.initial(), Fruit.initial(), Fruit.initial()],
  };
};

let draw = (state, env) => {
  Draw.image(state.background, ~pos=(0, 0), ~width=xmax, ~height=ymax, env);
  state.list_of_fruits
  |> List.iter(item =>
       Draw.subImagef(
         state.fruit_images[item.fruit_number],
         ~pos=(item.coordinate.x, item.coordinate.y),
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
    list_of_fruits: state.list_of_fruits |> List.map(updateItem),
  };
  state;
};

run(~setup, ~draw, ());