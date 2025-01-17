#include <DefaultComponentsRegistry.h>
#include <DefaultTurboModuleManagerDelegate.h>
#include <fbjni/fbjni.h>
#include <react/renderer/componentregistry/ComponentDescriptorProviderRegistry.h>
#include <rncli.h>

void registerComponents(
    std::shared_ptr<facebook::react::ComponentDescriptorProviderRegistry const>
        registry) {
  // Custom Fabric Components go here. You can register custom
  // components coming from your App or from 3rd party libraries here.
  //
  // providerRegistry->add(concreteComponentDescriptorProvider<
  //        AocViewerComponentDescriptor>());

  // By default we just use the components autolinked by RN CLI
  facebook::react::rncli_registerProviders(registry);
}

std::shared_ptr<facebook::react::TurboModule> provideModules(
    const std::string &name,
    const facebook::react::JavaTurboModule::InitParams &params) {
  // Here you can provide your own module provider for TurboModules coming from
  // either your application or from external libraries. The approach to follow
  // is similar to the following (for a library called `samplelibrary`):
  //
  // auto module = samplelibrary_ModuleProvider(moduleName, params);
  // if (module != nullptr) {
  //    return module;
  // }
  // return rncore_ModuleProvider(moduleName, params);

  // By default we just use the module providers autolinked by RN CLI
  return facebook::react::rncli_ModuleProvider(name, params);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
  return facebook::jni::initialize(vm, [] {
    facebook::react::DefaultTurboModuleManagerDelegate::
        moduleProvidersFromEntryPoint = &provideModules;
    facebook::react::DefaultComponentsRegistry::
        registerComponentDescriptorsFromEntryPoint = &registerComponents;
  });
}
