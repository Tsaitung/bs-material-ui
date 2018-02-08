# Reason bindings for material-ui
This library provides Reason bindings for
[material-ui](https://material-ui-next.com/). It's automatically generated by
[reason-mui-binding-generator](https://github.com/jsiebern/reason-mui-binding-generator).

*These bindings are mostly complete, just a few more indepth use cases (Theming etc.) are missing. I use them in production daily by now, still, if you encounter any problems please feel free to open an issue*

## Installation (for your Reason project)

Run:

    yarn add jsiebern/bs-material-ui

to add the library to your project dependencies. And add `bs-material-ui` to the `bs-dependencies` node of your `bsconfig.json`.

## Installation of the `withStyles` code extension (ppx)

Add the entry `bs-material-ui/ppx_withStyles` to the `ppx-flags` node of your `bsconfig.json`.

## Example

Please see [the examples folder](https://github.com/jsiebern/bs-material-ui/tree/master/src).

## withStyles

In material-ui, the `withStyles` [HOC](https://reactjs.org/docs/higher-order-components.html) takes care of turning React styles into CSS via [react-jss](https://github.com/cssinjs/react-jss). It passes a `classes` prop onto the component with the first level keys of the style object passed on.

HOC do not translate well into Reason which is why we are using a [render prop](http://reactpatterns.com/#render-callback) to make things easier. [(More information on the topic).](https://www.youtube.com/watch?v=BcVAq3YFiuc)

## withStyles Example PPX (typesafe)

**Make sure you have implemented the ppx file (see installation for reference)**

The code extension allows you to write a typesafe styled component with ease. It follows the format `[%mui.withStyles "ComponentName"({ className: ReactDOMRe.Style.t })]`. The generated Component has a render function which passes on a `record` with the class keys. See the example below.

```reason
let component = ReasonReact.statelessComponent("Example");

[%mui.withStyles
  "StyledExample"({
    alignRight: ReactDOMRe.Style.make(~width="100%", ~textAlign="right", ())
  })
];

let make = _children => {
  ...component,
  render: _self =>
    <StyledExample
      render=(
        classes =>
          <div className=classes.alignRight>
            (
              ReasonReact.stringToElement("Example text - aligned to the right")
            )
          </div>
      )
    />
};
```

## withStyles Example (unsafe)
You need to pass a `classes` prop of type `list( { name: string, styles: ReactDOMRe.Style.t } )` and a `render` function to the component. See the following example:

```reason
let component = ReasonReact.statelessComponent("Example");

let make = _children => {
  ...component,
  render: _self =>
    <MaterialUi.WithStyles
      classes=[
        {
          name: "alignRight",
          styles: ReactDOMRe.Style.make(~width="100%", ~textAlign="right", ())
        }
      ]
      render=(
        classes =>
          <div className=classes##alignRight>
            (
              ReasonReact.stringToElement("Example text - aligned to the right")
            )
          </div>
      )
    />
};
```

## Colors

All Colors are accessible in Submodules of the Module `Colors`. Color keys that are a pure number begin with a `c`. [(MUI Docs Reference).](https://material-ui-next.com/style/color/)

Example:

```reason
[%mui.withStyles
  "ColorExample"({
    bgColor: ReactDOMRe.Style.make(~backgroundColor=MaterialUi.Colors.Red.c300, ())
  })
];
```

## Overriding with classes

To take advantage of Reasons type system when overriding classes directly on components they have been converted into Variants and need to be passed as a `list` to the components `classes` prop. It is best used in combination with the `MaterialUi.WithStyles` component.

[(MUI Docs Reference).](https://material-ui-1dab0.firebaseapp.com/customization/overrides/#overriding-with-classes)

Example:
```reason
let component = ReasonReact.statelessComponent("Example");

[%mui.withStyles
  "OverrideExample"({
    fontSize: ReactDOMRe.Style.make(~fontSize="30px", ()),
    bgColor:
      ReactDOMRe.Style.make(~backgroundColor=MaterialUi.Colors.Red.c300, ())
  })
];

let make = _children => {
  ...component,
  render: _self =>
    <OverrideExample
      render=(
        classes =>
          <MaterialUi.Button
            color=`Primary
            variant=`Raised
            classes=[Root(classes.fontSize), RaisedPrimary(classes.bgColor)]>
            (ReasonReact.stringToElement("Example Button"))
          </MaterialUi.Button>
      )
    />
};
```

## Todo
- [ ] Implement the whole `Theme` structure & create a converter for it
- [x] ~~Write a code extension for conveniently using a typesafe `withStyles`~~ (2018-02-08)
- [ ] Make the code extension work with `theme => object` function
- [x] ~~Expose a nested `Colors` module~~ (2017-11-15)
- [x] ~~Think of a way to use `theme => object` pattern as `withStyles` argument~~(2017-11-25)
- [ ] Add `WithTheme` component
- [ ] Add `ThemeProvider` component
- [x] ~~Implement classname overrides~~ (2017-11-15)
- [ ] Implement ref function signatures