#!/usr/bin/env bash
# Modified by however-yir autonomous driving team.
set -euo pipefail

TARGET_BRANCH="${1:-master}"
UPSTREAM_URL="${2:-https://github.com/ApolloAuto/apollo.git}"

if ! git remote | grep -q '^upstream$'; then
  git remote add upstream "${UPSTREAM_URL}"
fi

git fetch upstream

git checkout "${TARGET_BRANCH}"
git pull --ff-only origin "${TARGET_BRANCH}"

if ! git rebase "upstream/${TARGET_BRANCH}"; then
  echo "[rebase] conflict detected; aborting rebase"
  git rebase --abort
  exit 2
fi

git push origin "${TARGET_BRANCH}"

echo "[rebase] completed: ${TARGET_BRANCH} <- upstream/${TARGET_BRANCH}"
