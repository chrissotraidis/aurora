#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace aurora::input::detail {

struct ControllerSnapshot {
  uint32_t instance = 0;
  int32_t player = -1;
  bool connected = false;
};

struct ControllerAssignment {
  uint32_t instance = 0;
  int32_t player = -1;
};

struct ControllerReconcilePlan {
  std::vector<uint32_t> close;
  std::vector<uint32_t> open;
  std::vector<ControllerAssignment> assign;
};

inline ControllerReconcilePlan plan_controller_reconciliation(
    const std::vector<ControllerSnapshot>& stored, const std::vector<uint32_t>& current, int32_t maxPlayers) {
  ControllerReconcilePlan plan;
  std::vector<bool> occupied(static_cast<size_t>(std::max(maxPlayers, 0)), false);

  const auto isCurrent = [&current](uint32_t instance) {
    return std::find(current.begin(), current.end(), instance) != current.end();
  };
  const auto isStoredAndValid = [&stored](uint32_t instance) {
    return std::any_of(stored.begin(), stored.end(), [instance](const ControllerSnapshot& controller) {
      return controller.instance == instance && controller.connected;
    });
  };

  for (const auto& controller : stored) {
    if (!controller.connected || !isCurrent(controller.instance)) {
      plan.close.push_back(controller.instance);
      continue;
    }
    if (controller.player >= 0 && controller.player < maxPlayers) {
      occupied[static_cast<size_t>(controller.player)] = true;
    }
  }

  for (uint32_t instance : current) {
    if (!isStoredAndValid(instance)) {
      plan.open.push_back(instance);
    }
  }

  for (uint32_t instance : plan.open) {
    const auto freePlayer = std::find(occupied.begin(), occupied.end(), false);
    const int32_t player = freePlayer == occupied.end()
                               ? -1
                               : static_cast<int32_t>(std::distance(occupied.begin(), freePlayer));
    if (player >= 0) {
      occupied[static_cast<size_t>(player)] = true;
    }
    plan.assign.push_back({instance, player});
  }

  return plan;
}

} // namespace aurora::input::detail
