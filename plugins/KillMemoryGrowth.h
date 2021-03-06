/*
 * Copyright (C) 2018-present, Facebook, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include <chrono>
#include <unordered_set>

#include "oomd/plugins/BaseKillPlugin.h"

namespace Oomd {

template <typename Base = BaseKillPlugin>
class KillMemoryGrowth : public Base {
 public:
  int init(
      Engine::MonitoredResources& resources,
      const Engine::PluginArgs& args) override;

  Engine::PluginRet run(OomdContext& ctx) override;

  static KillMemoryGrowth* create() {
    return new KillMemoryGrowth();
  }

  ~KillMemoryGrowth() = default;

 protected:
  virtual bool tryToKillBySize(OomdContext& ctx, bool ignore_threshold);
  virtual bool tryToKillByGrowth(OomdContext& ctx);

  std::unordered_set<CgroupPath> cgroups_;
  int size_threshold_{50};
  int growing_size_percentile_{80};
  float min_growth_ratio_{1.25};
  int post_action_delay_{15};
  bool dry_{false};
  bool debug_{false};
};

} // namespace Oomd

#include "oomd/plugins/KillMemoryGrowth-inl.h"
