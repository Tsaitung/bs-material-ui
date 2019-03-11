module Timeout_shape = {
  [@bs.deriving abstract]
  type t = {
    [@bs.optional]
    enter: [ | `Int(int) | `Float(float)],
    [@bs.optional]
    exit: [ | `Int(int) | `Float(float)],
  };
  let make = t;

  let unwrap = (obj: t) => {
    let unwrappedMap = Js.Dict.empty();

    switch (
      obj->enterGet->(Belt.Option.map(v => MaterialUi_Helpers.unwrapValue(v)))
    ) {
    | Some(v) =>
      unwrappedMap->(Js.Dict.set("enter", v->MaterialUi_Helpers.toJsUnsafe))
    | None => ()
    };

    switch (
      obj->exitGet->(Belt.Option.map(v => MaterialUi_Helpers.unwrapValue(v)))
    ) {
    | Some(v) =>
      unwrappedMap->(Js.Dict.set("exit", v->MaterialUi_Helpers.toJsUnsafe))
    | None => ()
    };

    unwrappedMap;
  };
};

[@bs.obj]
external makePropsMui:
  (
    ~children: 'children=?,
    ~_in: bool=?,
    ~onEnter: ReactEvent.Synthetic.t => unit=?,
    ~onExit: ReactEvent.Synthetic.t => unit=?,
    ~theme: Js.t({..})=?,
    ~timeout: 'union_r5fu=?,
    unit
  ) =>
  _ =
  "";

[@bs.module "@material-ui/core"]
external reactComponent: React.component('a) = "Zoom";

[@react.component]
let make =
    (
      ~children: option('children)=?,
      ~in_: option(bool)=?,
      ~onEnter: option(ReactEvent.Synthetic.t => unit)=?,
      ~onExit: option(ReactEvent.Synthetic.t => unit)=?,
      ~theme: option(Js.t({..}))=?,
      ~timeout:
         option([ | `Int(int) | `Float(float) | `Object(Timeout_shape.t)])=?,
    ) =>
  React.createElement(
    reactComponent,
    makePropsMui(
      ~children?,
      ~_in=?in_,
      ~onEnter?,
      ~onExit?,
      ~theme?,
      ~timeout=?
        timeout->(Belt.Option.map(v => MaterialUi_Helpers.unwrapValue(v))),
      (),
    ),
  );