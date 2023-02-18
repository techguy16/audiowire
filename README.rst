AudioWire
===========

AudioWire is a modular session / policy manager for
`PipeWire <https://pipewire.org>`_ and a GObject-based high-level library
that wraps PipeWire's API, providing convenience for writing the daemon's
modules as well as external tools for managing PipeWire.

The AudioWire daemon implements the session & policy management service.
It follows a modular design, having plugins that implement the actual
management functionality.

The AudioWire Library provides API that allows you to extend the WirePlumber
daemon, to write management or status tools for PipeWire
(apps that don't do actual media streaming) and to write custom session managers
for embedded devices.
