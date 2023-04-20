---
title: "Instrukcja laboratorium systemów wbudowanych"
subtitle: "Ćwiczenie 6: Obsługa impulsatora i sterowanie z histerezą"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: yes
titlepage-logo: "logo.jpg"
colorlinks: yes
header-includes: |
  \usepackage{awesomebox}
  \usepackage{gensymb}
...

> When you finally understand what you are doing, things will go right.
>
> — _Bill Fairbank_

# Cel ćwiczenia

Celem ćwiczenia jest zapoznanie się z:

* podstawami standardu 1-Wire,
* wykorzystaniem termometru DS18B20.

# Uruchomienie programu wyjściowego

1. Umieść zworki na pinach `RS`, `E` i `D4`…`D7` złącza `J10` (na lewo od buzzera).
1. Zworkę `J15` (nad buzzerem) ustaw w pozycji `RW->GND`.
1. Umieść wyświetlacz w złączu `DIS1`.
1. Podłącz pin `1WIRE` złącza `J22` (pod termometrem) do pinu `PC0` mikrokontrolera.
1. Po włączeniu zasilania wyświetlacz pokaże identyfikator `0x00000000000000` oraz temperaturę `0`.

# Zadanie podstawowe

## Wymagania funkcjonalne

1. 

## Modyfikacja programu

# Zadanie rozszerzone

## Wymagania funkcjonalne

## Modyfikacja programu

