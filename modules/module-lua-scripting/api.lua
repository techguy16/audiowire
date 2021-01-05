-- WirePlumber
--
-- This file contains the API that is made available to the Lua scripts
--
-- Copyright © 2020 Collabora Ltd.
--    @author George Kiagiadakis <george.kiagiadakis@collabora.com>
--
-- SPDX-License-Identifier: MIT

local function Constraint (spec)
  assert (type(spec[1]) == "string", "Constraint: expected subject as string");
  assert (type(spec[2]) == "string", "Constraint: expected verb as string");

  local subject = spec[1]
  local verb = spec[2]
  local verbs = {
    ["="] = "equals",
    ["c"] = "in-list",
    ["~"] = "in-range",
    ["#"] = "matches",
    ["+"] = "is-present",
    ["-"] = "is-absent"
  }

  -- check and convert verb to its short version
  local verb_is_valid = false
  for k, v in pairs(verbs) do
    if verb == k or verb == v then
      verb = k
      spec[2] = k
      verb_is_valid = true
      break
    end
  end
  assert (verb_is_valid, "Constraint: invalid verb '" .. verb .. "'")

  -- check and convert type to its integer value
  local type = spec["type"]
  if type then
    local valid_types = { "pw-global", "pw", "gobject" }
    local type_is_valid = false

    for i, v in ipairs(valid_types) do
      if type == v then
        spec["type"] = i
        type_is_valid = true
        break
      end
    end

    assert(type_is_valid, "Constraint: invalid subject type '" .. type .. "'")
  end

  -- check if we got the right amount of values
  if verb == "=" or verb == "#" then
    assert (spec[3] ~= nil,
      "Constraint: " .. verbs[verb] .. ": expected constraint value")
  elseif verb == "c" then
    assert (spec[3] ~= nil,
      "Constraint: " .. verbs[verb] .. ": expected at least one constraint value")
  elseif verb == "~" then
    assert (spec[3] ~= nil and spec[4] ~= nil,
      "Constraint: " .. verbs[verb] .. ": expected two values")
  else
    assert (spec[3] == nil,
      "Constraint: " .. verbs[verb] .. ": expected no value, but there is one")
  end

  return debug.setmetatable(spec, { __name = "Constraint" })
end

SANDBOX_EXPORT = {
  Log = WpDebug,
  ObjectManager = WpObjectManager_new,
  Interest = WpObjectInterest_new,
  Constraint = Constraint,
}