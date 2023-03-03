# krig keyboard layouts

This folder documents my keyboard layouts.

I tried breaking my keymaps out into a separate repository,
but this setup broke with 0.20.0 and I don't have the energy
to make it work again. The solution wasn't very clean anyway
and it interferes with LSP etc...

## Keyboards

* EZ Planck: `keyboards/planck/keymaps/krig/`
* Drop Preonic (rev3): `keyboards/preonic/keymaps/krig/`
* Ramaworks m50a: `keyboards/wilba_tech/rama_works_m50_a/keymaps/krig/`

## Building and flashing

```
qmk compile -kb wilba_tech/rama_works_m50_a -km krig
qmk compile -kb planck/ez/glow -km krig
qmk compile -kb preonic/rev3 -km krig

qmk flash -kb wilba_tech/rama_works_m50_a -km krig
qmk flash -kb planck/ez/glow -km krig
qmk flash -kb preonic/rev3 -km krig
```

## symbol layer

Experimental symbol layer for Planck based on this blog post:

https://getreuer.info/posts/keyboards/symbol-layer/index.html

## Planck

![planck](planck.png "planck layout")
