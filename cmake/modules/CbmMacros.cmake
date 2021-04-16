function(download_project_if_needed)
  include(DownloadProject)
  set(oneValueArgs PROJECT GIT_REPOSITORY GIT_TAG GIT_STASH SOURCE_DIR TEST_FILE)
  cmake_parse_arguments(MY "" "${oneValueArgs}"
                       "" ${ARGN} )

  Set(ProjectUpdated FALSE PARENT_SCOPE)

  If(NOT EXISTS ${MY_SOURCE_DIR}/${MY_TEST_FILE})
    download_project(PROJ            ${MY_PROJECT}
                     GIT_REPOSITORY  ${MY_GIT_REPOSITORY}
                     GIT_TAG         ${MY_GIT_TAG}
                     SOURCE_DIR      ${MY_SOURCE_DIR}
                    )
  Else()
    Execute_process(COMMAND git rev-parse HEAD
                    WORKING_DIRECTORY ${MY_SOURCE_DIR}
                    OUTPUT_VARIABLE CURRENT_SPADIC_HASH
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                   )
    If(NOT ${MY_GIT_TAG} STREQUAL ${CURRENT_SPADIC_HASH})
      If(MY_GIT_STASH)
        Execute_Process(COMMAND git stash  WORKING_DIRECTORY ${MY_SOURCE_DIR}) 
        Execute_Process(COMMAND git stash clear  WORKING_DIRECTORY ${MY_SOURCE_DIR}) 
      EndIF()
      download_project(PROJ            ${MY_PROJECT}
                       GIT_REPOSITORY  ${MY_GIT_REPOSITORY}
                       GIT_TAG         ${MY_GIT_TAG}
                       SOURCE_DIR      ${MY_SOURCE_DIR}
                      )
      Set(ProjectUpdated TRUE PARENT_SCOPE)
    EndIf()
  EndIf()
EndFunction()

