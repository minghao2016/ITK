set(CTEST_BUILD_NAME "${platform}-${compiler}-$ENV{GERRIT_TOPIC}-$ENV{GERRIT_CHANGE_NUMBER}-$ENV{GERRIT_PATCHSET_NUMBER}")
set(dashboard_git_branch "$ENV{GERRIT_TOPIC}-$ENV{GERRIT_CHANGE_NUMBER}-$ENV{GERRIT_PATCHSET_NUMBER}")
set(dashboard_no_update 1)
set(dashboard_model "Experimental")
set(dashboard_track "Gerrit")
set(dashboard_no_clean 1)