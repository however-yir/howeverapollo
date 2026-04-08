#!/bin/bash
###############################################################################
# Copyright 2017 The Apollo Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###############################################################################

##Install
#$APOLLO_ROOT/scripts/deploy_local_sanity_check.sh

##Uninstall
#$APOLLO_ROOT/scripts/deploy_local_sanity_check.sh -u

APOLLO_ROOT=$(cd $(dirname $0)/.. && pwd)
APOLLO_FILE="modules/dreamview"
DRY_RUN=0
DO_UNINSTALL=0

. $APOLLO_ROOT/scripts/apollo_base.sh

while [ $# -gt 0 ]; do
  case "$1" in
    -u) DO_UNINSTALL=1 ;;
    --dry-run) DRY_RUN=1 ;;
    *) ;;
  esac
  shift
done

function uninstall() {
  if [ -L "$APOLLO_ROOT/.git/hooks/post-commit" ]; then
    if [ "$DRY_RUN" -eq 1 ]; then
      info "[dry-run] would remove $APOLLO_ROOT/.git/hooks/post-commit"
      return 0
    fi
    pushd $APOLLO_ROOT/.git/hooks > /dev/null
    rm post-commit
    popd > /dev/null
    ok "sanity check was removed."
  elif [ "$DRY_RUN" -eq 1 ]; then
    info "[dry-run] post-commit hook symlink not found, nothing to remove."
  fi
}

if [ "$DO_UNINSTALL" -eq 1 ]; then
  uninstall
  exit 0
fi

if [ "$DRY_RUN" -eq 0 ]; then
  if [ ! -e "$APOLLO_FILE" ]; then
    warning "Please run this script under Apollo source root dir."
    exit 1
  fi

  if [ ! -e "$APOLLO_ROOT/.git" ]; then
    warning "$APOLLO_ROOT seems not a git repo."
    exit 1
  fi

  type curl > /dev/null 2>&1 || {
    error >&2 "command curl not found, please install it with: sudo apt-get install curl"
    exit 1
  }
  type perl > /dev/null 2>&1 || {
    error >&2 "command perl not found, please install it with: sudo apt-get install perl-base"
    exit 1
  }
else
  info "Dry run mode enabled: skip dependency checks and filesystem mutations."
fi

HOOKS_URL="http://code.qt.io/cgit/qt/qtrepotools.git/plain/git-hooks"
HOOKS_DIR=$APOLLO_ROOT/tools/git-hooks
HOOK_SCRITPS="git_post_commit_hook sanitize-commit"

if [ ! -e $HOOKS_DIR ]; then
  if [ "$DRY_RUN" -eq 1 ]; then
    info "[dry-run] would create directory: $HOOKS_DIR"
  else
    mkdir -p $HOOKS_DIR
  fi
fi

if [ "$DRY_RUN" -eq 0 ]; then
  pushd $HOOKS_DIR > /dev/null || error "Enter $HOOKS_DIR failed."
fi

for i in $HOOK_SCRITPS; do
  if [ ! -e "$HOOKS_DIR/$i" ]; then
    if [ "$DRY_RUN" -eq 1 ]; then
      info "[dry-run] would download $HOOKS_URL/$i"
      continue
    fi
    curl -O $HOOKS_URL/$i
    if [ $? -ne 0 ]; then
      error "Failed to pull hooks: $i ."
    fi
    chmod +x $i
  fi
done

if [ "$DRY_RUN" -eq 0 ]; then
  popd > /dev/null
fi

if [ ! -e "$APOLLO_ROOT/.git/hooks/post-commit" ]; then
  if [ "$DRY_RUN" -eq 1 ]; then
    info "[dry-run] would link $HOOKS_DIR/git_post_commit_hook -> $APOLLO_ROOT/.git/hooks/post-commit"
    ok "Dry run finished."
    exit 0
  fi
  pushd $APOLLO_ROOT/.git/hooks > /dev/null || error "Enter target dir failed. "
  #info "deploy hooks..."
  ln -s $HOOKS_DIR/git_post_commit_hook post-commit
  if [ $? -eq 0 ]; then
    ok "Deploy sanity check done."
  else
    error "Failed to deploy sanity check."
  fi
  popd > /dev/null
elif [ -L "$APOLLO_ROOT/.git/hooks/post-commit" ]; then
  info "Sanity check seems already deployed."
elif [ -f "$APOLLO_ROOT/.git/hooks/post-commit" ]; then
  info "$APOLLO_ROOT/.git/hooks/post-commit hook seems already exists, please backup it and run this script again."
fi
