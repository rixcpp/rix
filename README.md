<table>
  <tr>
    <td valign="top" width="68%">

<h1>Rix</h1>

<p>
  <a href="https://x.com/vixcpp">
    <img src="https://img.shields.io/badge/X-Follow-black?logo=x" alt="X" />
  </a>
  <a href="https://www.youtube.com/@vixcpp">
    <img src="https://img.shields.io/badge/YouTube-Subscribe-red?logo=youtube" alt="YouTube" />
  </a>
  <img src="https://img.shields.io/github/stars/rixcpp/rix?style=flat" alt="Stars" />
  <img src="https://img.shields.io/github/forks/rixcpp/rix?style=flat" alt="Forks" />
</p>

<p>
  <b>Rix</b> is the foundational standard library of <b>Vix.cpp</b>.<br/>
  A minimal, deterministic, modular base layer for modern C++ systems.
</p>

<p>
  🌍 <a href="https://vixcpp.com">vixcpp.com</a><br />
  📘 <a href="https://vixcpp.com/docs">Documentation</a>
</p>

</td>
  <td valign="top" width="32%" align="right">
      <img src="https://res.cloudinary.com/dwjbed2xb/image/upload/v1766830420/banniere_qfghep.png" alt="Rix Logo"
        width="260"/>
    </td>
  </tr>
</table>

<hr />

## C++ is powerful. But it is not cohesive.

Modern C++ gives you:

- The STL
- Boost
- Header-only utilities
- Third-party abstractions
- Countless competing patterns

But it does not give you:

- A coherent runtime-grade foundation
- Deterministic IO semantics
- Predictable memory boundaries
- A minimal, unified systems layer
- A philosophy aligned with runtime design

When building a runtime like Vix, this fragmentation becomes a liability.

---

## Why Rix exists

Rix exists because Vix cannot depend on:

- Implicit behavior
- Hidden global state
- Surprising allocations
- Over-engineered abstractions
- Inconsistent error models

A runtime must be:

- Auditable
- Deterministic
- Stable
- Maintainable for years
- Predictable under load

Rix provides that base layer.

---

## The current ecosystem problem

Today, building serious C++ systems often means:

- Mixing STL + Boost + random libraries
- Fighting API inconsistencies
- Debugging hidden behavior
- Managing dependency chaos
- Losing control over runtime guarantees

There is no small, curated, opinionated foundation.

Rust has one.
Go has one.
Deno has one.

C++ does not.

Rix is an attempt to restore cohesion.

---

## Rix is not trying to replace the STL

Rix does not compete with the standard library.

It complements it.

It provides:

- A consistent minimal surface
- Explicit modular boundaries
- Runtime-first design
- Long-term stability
- Controlled abstractions

It is intentionally small.

It is intentionally opinionated.

It is intentionally boring.

---

## Designed for Vix. Useful beyond Vix.

Rix was built for:

- A modern C++ runtime
- Offline-first systems
- High-performance backends
- Deterministic network services
- Embedded and constrained environments

But any modern C++ project that values:

- Predictability
- Simplicity
- Modular architecture

can benefit from it.

## Philosophy

- Explicit over implicit
- Deterministic over magical
- Modular over monolithic
- Small over complex
- Runtime-first design

## Status

Rix is under active development as part of the Vix ecosystem.

Each module is versioned independently.
The umbrella project provides a unified integration layer.

## License

MIT License

Copyright (c) 2026 Vix.cpp
Authors: Gaspard Kirira
