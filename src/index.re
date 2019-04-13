open Reprocessing;

type vector = {
  x: float,
  y: float,
};

type itemKind =
  | Banana
  | Apple
  | Coconut
  | Pineapple
  | Watermelon
  | Bomb;

type itemType = {
  kind: itemKind,
  vector,
  coordinate: vector,
};

type stateT = {
  listofitem: list(itemType),
  bananaImage: imageT,
  appleImage: imageT,
  coconutImage: imageT,
  pineappleImage: imageT,
  watermelonImage: imageT,
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
  Env.size(~width=800, ~height=800, env);
  {
    listofitem: [
      {
        kind: Coconut,
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
        kind: Apple,
        vector: {
          x: 0.5,
          y: 0.1,
        },
        coordinate: {
          x: 0.0,
          y: 200.0,
        },
      },
      {
        kind: Banana,
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
        kind: Watermelon,
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
        kind: Pineapple,
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
        kind: Bomb,
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
        kind: Bomb,
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
        kind: Bomb,
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
    bananaImage: Draw.loadImage(~filename="./assets/banana_small.png", env),
    appleImage: Draw.loadImage(~filename="assets/apple_small.png", env),
    coconutImage: Draw.loadImage(~filename="assets/coconut_small.png", env),
    pineappleImage:
      Draw.loadImage(~filename="assets/pineapple_small.png", env),
    watermelonImage:
      Draw.loadImage(~filename="assets/watermelon_small.png", env),
    bombImage: Draw.loadImage(~filename="assets/bomb_small.png", env),
  };
};

let draw = (state, env) => {
  Draw.background(Utils.color(~r=255, ~g=217, ~b=229, ~a=255), env);
  Draw.fill(Utils.color(~r=41, ~g=166, ~b=244, ~a=255), env);

  List.iter(
    item =>
      switch (item.kind) {
      | Banana =>
        Draw.subImagef(
          state.bananaImage,
          ~pos=(item.coordinate.x, item.coordinate.y),
          ~width=100.,
          ~height=100.,
          ~texPos=(0, 0),
          ~texWidth=100,
          ~texHeight=100,
          env,
        )
      | Apple =>
        Draw.subImagef(
          state.appleImage,
          ~pos=(item.coordinate.x, item.coordinate.y),
          ~width=64.,
          ~height=70.,
          ~texPos=(0, 0),
          ~texWidth=100,
          ~texHeight=100,
          env,
        )
      | Coconut =>
        Draw.subImagef(
          state.coconutImage,
          ~pos=(item.coordinate.x, item.coordinate.y),
          ~width=100.,
          ~height=100.,
          ~texPos=(0, 0),
          ~texWidth=100,
          ~texHeight=100,
          env,
        )
      | Pineapple =>
        Draw.subImagef(
          state.pineappleImage,
          ~pos=(item.coordinate.x, item.coordinate.y),
          ~width=100.,
          ~height=100.,
          ~texPos=(0, 0),
          ~texWidth=100,
          ~texHeight=100,
          env,
        )
      | Watermelon =>
        Draw.subImagef(
          state.watermelonImage,
          ~pos=(item.coordinate.x, item.coordinate.y),
          ~width=100.,
          ~height=100.,
          ~texPos=(0, 0),
          ~texWidth=100,
          ~texHeight=100,
          env,
        )
      | Bomb =>
        Draw.subImagef(
          state.bombImage,
          ~pos=(item.coordinate.x, item.coordinate.y),
          ~width=100.,
          ~height=100.,
          ~texPos=(0, 0),
          ~texWidth=100,
          ~texHeight=100,
          env,
        )
      },
    state.listofitem,
  );

  let state = {
    ...state,
    listofitem: state.listofitem |> List.map(updateItem),
  };
  state;
};

run(~setup, ~draw, ());